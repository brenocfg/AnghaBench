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
struct inode {int /*<<< orphan*/  i_data; } ;
struct dentry {int dummy; } ;
struct ceph_readdir_cache_control {unsigned int index; struct dentry** dentries; int /*<<< orphan*/  page; } ;
struct ceph_mds_request {scalar_t__ r_dir_release_cnt; scalar_t__ r_dir_ordered_cnt; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_ordered_count; int /*<<< orphan*/  i_release_count; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SIZE ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  ceph_readdir_cache_release (struct ceph_readdir_cache_control*) ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 int /*<<< orphan*/  find_lock_page (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  grab_cache_page (int /*<<< orphan*/ *,scalar_t__) ; 
 struct dentry** kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dentry**,int /*<<< orphan*/ ,int) ; 
 scalar_t__ page_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_readdir_cache(struct inode *dir, struct dentry *dn,
			      struct ceph_readdir_cache_control *ctl,
			      struct ceph_mds_request *req)
{
	struct ceph_inode_info *ci = ceph_inode(dir);
	unsigned nsize = PAGE_SIZE / sizeof(struct dentry*);
	unsigned idx = ctl->index % nsize;
	pgoff_t pgoff = ctl->index / nsize;

	if (!ctl->page || pgoff != page_index(ctl->page)) {
		ceph_readdir_cache_release(ctl);
		if (idx == 0)
			ctl->page = grab_cache_page(&dir->i_data, pgoff);
		else
			ctl->page = find_lock_page(&dir->i_data, pgoff);
		if (!ctl->page) {
			ctl->index = -1;
			return idx == 0 ? -ENOMEM : 0;
		}
		/* reading/filling the cache are serialized by
		 * i_mutex, no need to use page lock */
		unlock_page(ctl->page);
		ctl->dentries = kmap(ctl->page);
		if (idx == 0)
			memset(ctl->dentries, 0, PAGE_SIZE);
	}

	if (req->r_dir_release_cnt == atomic64_read(&ci->i_release_count) &&
	    req->r_dir_ordered_cnt == atomic64_read(&ci->i_ordered_count)) {
		dout("readdir cache dn %p idx %d\n", dn, ctl->index);
		ctl->dentries[idx] = dn;
		ctl->index++;
	} else {
		dout("disable readdir cache\n");
		ctl->index = -1;
	}
	return 0;
}