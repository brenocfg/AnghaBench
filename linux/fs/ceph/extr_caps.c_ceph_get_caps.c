#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct file {struct ceph_file_info* private_data; } ;
struct ceph_inode_info {scalar_t__ i_inline_version; int /*<<< orphan*/  i_cap_wq; } ;
struct ceph_fs_client {int /*<<< orphan*/  filp_gen; } ;
struct ceph_file_info {int fmode; scalar_t__ filp_gen; int /*<<< orphan*/  num_locks; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int CEPH_CAP_FILE_CACHE ; 
 int CEPH_CAP_FILE_LAZYIO ; 
 int CEPH_CAP_FILE_RD ; 
 int CEPH_FILE_MODE_WR ; 
 scalar_t__ CEPH_INLINE_NONE ; 
 int /*<<< orphan*/  CEPH_STAT_CAP_INLINE_DATA ; 
 int CHECK_FILELOCK ; 
 int /*<<< orphan*/  DEFINE_WAIT_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EBADF ; 
 int ERESTARTSYS ; 
 int ESTALE ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int NON_BLOCKING ; 
 scalar_t__ PageUptodate (struct page*) ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int __ceph_do_getattr (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_fscache_revalidate_cookie (struct ceph_inode_info*) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 struct ceph_fs_client* ceph_inode_to_client (struct inode*) ; 
 int ceph_pool_perm_check (struct inode*,int) ; 
 int /*<<< orphan*/  ceph_put_cap_refs (struct ceph_inode_info*,int) ; 
 int ceph_renew_caps (struct inode*) ; 
 int /*<<< orphan*/  check_max_size (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 struct inode* file_inode (struct file*) ; 
 struct page* find_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int try_get_cap_refs (struct inode*,int,int,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wait_woken (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  woken_wake_function ; 

int ceph_get_caps(struct file *filp, int need, int want,
		  loff_t endoff, int *got, struct page **pinned_page)
{
	struct ceph_file_info *fi = filp->private_data;
	struct inode *inode = file_inode(filp);
	struct ceph_inode_info *ci = ceph_inode(inode);
	struct ceph_fs_client *fsc = ceph_inode_to_client(inode);
	int ret, _got, flags;

	ret = ceph_pool_perm_check(inode, need);
	if (ret < 0)
		return ret;

	if ((fi->fmode & CEPH_FILE_MODE_WR) &&
	    fi->filp_gen != READ_ONCE(fsc->filp_gen))
		return -EBADF;

	while (true) {
		if (endoff > 0)
			check_max_size(inode, endoff);

		flags = atomic_read(&fi->num_locks) ? CHECK_FILELOCK : 0;
		_got = 0;
		ret = try_get_cap_refs(inode, need, want, endoff,
				       flags, &_got);
		if (ret == -EAGAIN)
			continue;
		if (!ret) {
			DEFINE_WAIT_FUNC(wait, woken_wake_function);
			add_wait_queue(&ci->i_cap_wq, &wait);

			flags |= NON_BLOCKING;
			while (!(ret = try_get_cap_refs(inode, need, want,
							endoff, flags, &_got))) {
				if (signal_pending(current)) {
					ret = -ERESTARTSYS;
					break;
				}
				wait_woken(&wait, TASK_INTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT);
			}

			remove_wait_queue(&ci->i_cap_wq, &wait);
			if (ret == -EAGAIN)
				continue;
		}

		if ((fi->fmode & CEPH_FILE_MODE_WR) &&
		    fi->filp_gen != READ_ONCE(fsc->filp_gen)) {
			if (ret >= 0 && _got)
				ceph_put_cap_refs(ci, _got);
			return -EBADF;
		}

		if (ret < 0) {
			if (ret == -ESTALE) {
				/* session was killed, try renew caps */
				ret = ceph_renew_caps(inode);
				if (ret == 0)
					continue;
			}
			return ret;
		}

		if (ci->i_inline_version != CEPH_INLINE_NONE &&
		    (_got & (CEPH_CAP_FILE_CACHE|CEPH_CAP_FILE_LAZYIO)) &&
		    i_size_read(inode) > 0) {
			struct page *page =
				find_get_page(inode->i_mapping, 0);
			if (page) {
				if (PageUptodate(page)) {
					*pinned_page = page;
					break;
				}
				put_page(page);
			}
			/*
			 * drop cap refs first because getattr while
			 * holding * caps refs can cause deadlock.
			 */
			ceph_put_cap_refs(ci, _got);
			_got = 0;

			/*
			 * getattr request will bring inline data into
			 * page cache
			 */
			ret = __ceph_do_getattr(inode, NULL,
						CEPH_STAT_CAP_INLINE_DATA,
						true);
			if (ret < 0)
				return ret;
			continue;
		}
		break;
	}

	if ((_got & CEPH_CAP_FILE_RD) && (_got & CEPH_CAP_FILE_CACHE))
		ceph_fscache_revalidate_cookie(ci);

	*got = _got;
	return 0;
}