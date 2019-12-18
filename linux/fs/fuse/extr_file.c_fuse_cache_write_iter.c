#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kiocb {int ki_flags; int ki_pos; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct address_space* f_mapping; } ;
struct address_space {struct inode* host; } ;
typedef  scalar_t__ ssize_t ;
typedef  int loff_t ;
struct TYPE_4__ {int /*<<< orphan*/ * backing_dev_info; } ;
struct TYPE_3__ {scalar_t__ writeback_cache; } ;

/* Variables and functions */
 int IOCB_DIRECT ; 
 int PAGE_SHIFT ; 
 TYPE_2__* current ; 
 scalar_t__ file_remove_privs (struct file*) ; 
 scalar_t__ file_update_time (struct file*) ; 
 scalar_t__ filemap_write_and_wait_range (struct address_space*,int,int) ; 
 scalar_t__ fuse_perform_write (struct kiocb*,struct address_space*,struct iov_iter*,int) ; 
 scalar_t__ fuse_update_attributes (struct inode*,struct file*) ; 
 scalar_t__ generic_file_direct_write (struct kiocb*,struct iov_iter*) ; 
 scalar_t__ generic_file_write_iter (struct kiocb*,struct iov_iter*) ; 
 scalar_t__ generic_write_checks (struct kiocb*,struct iov_iter*) ; 
 scalar_t__ generic_write_sync (struct kiocb*,scalar_t__) ; 
 TYPE_1__* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/ * inode_to_bdi (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  invalidate_mapping_pages (struct address_space*,int,int) ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 

__attribute__((used)) static ssize_t fuse_cache_write_iter(struct kiocb *iocb, struct iov_iter *from)
{
	struct file *file = iocb->ki_filp;
	struct address_space *mapping = file->f_mapping;
	ssize_t written = 0;
	ssize_t written_buffered = 0;
	struct inode *inode = mapping->host;
	ssize_t err;
	loff_t endbyte = 0;

	if (get_fuse_conn(inode)->writeback_cache) {
		/* Update size (EOF optimization) and mode (SUID clearing) */
		err = fuse_update_attributes(mapping->host, file);
		if (err)
			return err;

		return generic_file_write_iter(iocb, from);
	}

	inode_lock(inode);

	/* We can write back this queue in page reclaim */
	current->backing_dev_info = inode_to_bdi(inode);

	err = generic_write_checks(iocb, from);
	if (err <= 0)
		goto out;

	err = file_remove_privs(file);
	if (err)
		goto out;

	err = file_update_time(file);
	if (err)
		goto out;

	if (iocb->ki_flags & IOCB_DIRECT) {
		loff_t pos = iocb->ki_pos;
		written = generic_file_direct_write(iocb, from);
		if (written < 0 || !iov_iter_count(from))
			goto out;

		pos += written;

		written_buffered = fuse_perform_write(iocb, mapping, from, pos);
		if (written_buffered < 0) {
			err = written_buffered;
			goto out;
		}
		endbyte = pos + written_buffered - 1;

		err = filemap_write_and_wait_range(file->f_mapping, pos,
						   endbyte);
		if (err)
			goto out;

		invalidate_mapping_pages(file->f_mapping,
					 pos >> PAGE_SHIFT,
					 endbyte >> PAGE_SHIFT);

		written += written_buffered;
		iocb->ki_pos = pos + written_buffered;
	} else {
		written = fuse_perform_write(iocb, mapping, from, iocb->ki_pos);
		if (written >= 0)
			iocb->ki_pos += written;
	}
out:
	current->backing_dev_info = NULL;
	inode_unlock(inode);
	if (written > 0)
		written = generic_write_sync(iocb, written);

	return written ? written : err;
}