#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kiocb {int ki_pos; int ki_flags; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct gfs2_holder {int dummy; } ;
struct file {struct address_space* f_mapping; } ;
struct address_space {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/ * backing_dev_info; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int IOCB_APPEND ; 
 int IOCB_DIRECT ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int PAGE_SHIFT ; 
 TYPE_1__* current ; 
 struct inode* file_inode (struct file*) ; 
 scalar_t__ file_remove_privs (struct file*) ; 
 scalar_t__ file_update_time (struct file*) ; 
 scalar_t__ filemap_write_and_wait_range (struct address_space*,int,int) ; 
 scalar_t__ generic_write_checks (struct kiocb*,struct iov_iter*) ; 
 scalar_t__ generic_write_sync (struct kiocb*,scalar_t__) ; 
 scalar_t__ gfs2_file_direct_write (struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 scalar_t__ gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_iomap_ops ; 
 scalar_t__ gfs2_rsqa_alloc (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_size_hint (struct file*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/ * inode_to_bdi (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  invalidate_mapping_pages (struct address_space*,int,int) ; 
 scalar_t__ iomap_file_buffered_write (struct kiocb*,struct iov_iter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t gfs2_file_write_iter(struct kiocb *iocb, struct iov_iter *from)
{
	struct file *file = iocb->ki_filp;
	struct inode *inode = file_inode(file);
	struct gfs2_inode *ip = GFS2_I(inode);
	ssize_t written = 0, ret;

	ret = gfs2_rsqa_alloc(ip);
	if (ret)
		return ret;

	gfs2_size_hint(file, iocb->ki_pos, iov_iter_count(from));

	if (iocb->ki_flags & IOCB_APPEND) {
		struct gfs2_holder gh;

		ret = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, 0, &gh);
		if (ret)
			return ret;
		gfs2_glock_dq_uninit(&gh);
	}

	inode_lock(inode);
	ret = generic_write_checks(iocb, from);
	if (ret <= 0)
		goto out;

	/* We can write back this queue in page reclaim */
	current->backing_dev_info = inode_to_bdi(inode);

	ret = file_remove_privs(file);
	if (ret)
		goto out2;

	ret = file_update_time(file);
	if (ret)
		goto out2;

	if (iocb->ki_flags & IOCB_DIRECT) {
		struct address_space *mapping = file->f_mapping;
		loff_t pos, endbyte;
		ssize_t buffered;

		written = gfs2_file_direct_write(iocb, from);
		if (written < 0 || !iov_iter_count(from))
			goto out2;

		ret = iomap_file_buffered_write(iocb, from, &gfs2_iomap_ops);
		if (unlikely(ret < 0))
			goto out2;
		buffered = ret;

		/*
		 * We need to ensure that the page cache pages are written to
		 * disk and invalidated to preserve the expected O_DIRECT
		 * semantics.
		 */
		pos = iocb->ki_pos;
		endbyte = pos + buffered - 1;
		ret = filemap_write_and_wait_range(mapping, pos, endbyte);
		if (!ret) {
			iocb->ki_pos += buffered;
			written += buffered;
			invalidate_mapping_pages(mapping,
						 pos >> PAGE_SHIFT,
						 endbyte >> PAGE_SHIFT);
		} else {
			/*
			 * We don't know how much we wrote, so just return
			 * the number of bytes which were direct-written
			 */
		}
	} else {
		ret = iomap_file_buffered_write(iocb, from, &gfs2_iomap_ops);
		if (likely(ret > 0))
			iocb->ki_pos += ret;
	}

out2:
	current->backing_dev_info = NULL;
out:
	inode_unlock(inode);
	if (likely(ret > 0)) {
		/* Handle various SYNC-type writes */
		ret = generic_write_sync(iocb, ret);
	}
	return written ? written : ret;
}