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
struct inode {int dummy; } ;
struct file {scalar_t__ f_pos; TYPE_1__* f_mapping; } ;
struct ceph_fs_client {int /*<<< orphan*/  max_file_size; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_STAT_CAP_SIZE ; 
 scalar_t__ ENXIO ; 
#define  SEEK_CUR 131 
#define  SEEK_DATA 130 
#define  SEEK_END 129 
#define  SEEK_HOLE 128 
 scalar_t__ ceph_do_getattr (struct inode*,int /*<<< orphan*/ ,int) ; 
 struct ceph_fs_client* ceph_inode_to_client (struct inode*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  max (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vfs_setpos (struct file*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static loff_t ceph_llseek(struct file *file, loff_t offset, int whence)
{
	struct inode *inode = file->f_mapping->host;
	struct ceph_fs_client *fsc = ceph_inode_to_client(inode);
	loff_t i_size;
	loff_t ret;

	inode_lock(inode);

	if (whence == SEEK_END || whence == SEEK_DATA || whence == SEEK_HOLE) {
		ret = ceph_do_getattr(inode, CEPH_STAT_CAP_SIZE, false);
		if (ret < 0)
			goto out;
	}

	i_size = i_size_read(inode);
	switch (whence) {
	case SEEK_END:
		offset += i_size;
		break;
	case SEEK_CUR:
		/*
		 * Here we special-case the lseek(fd, 0, SEEK_CUR)
		 * position-querying operation.  Avoid rewriting the "same"
		 * f_pos value back to the file because a concurrent read(),
		 * write() or lseek() might have altered it
		 */
		if (offset == 0) {
			ret = file->f_pos;
			goto out;
		}
		offset += file->f_pos;
		break;
	case SEEK_DATA:
		if (offset < 0 || offset >= i_size) {
			ret = -ENXIO;
			goto out;
		}
		break;
	case SEEK_HOLE:
		if (offset < 0 || offset >= i_size) {
			ret = -ENXIO;
			goto out;
		}
		offset = i_size;
		break;
	}

	ret = vfs_setpos(file, offset, max(i_size, fsc->max_file_size));

out:
	inode_unlock(inode);
	return ret;
}