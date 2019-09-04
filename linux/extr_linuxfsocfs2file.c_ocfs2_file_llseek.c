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
struct inode {TYPE_1__* i_sb; } ;
struct file {int f_pos; TYPE_2__* f_mapping; } ;
typedef  int loff_t ;
struct TYPE_4__ {struct inode* host; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_maxbytes; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SEEK_CUR 132 
#define  SEEK_DATA 131 
#define  SEEK_END 130 
#define  SEEK_HOLE 129 
#define  SEEK_SET 128 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_inode_lock (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int /*<<< orphan*/ ) ; 
 int ocfs2_seek_data_hole_offset (struct file*,int*,int) ; 
 int vfs_setpos (struct file*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static loff_t ocfs2_file_llseek(struct file *file, loff_t offset, int whence)
{
	struct inode *inode = file->f_mapping->host;
	int ret = 0;

	inode_lock(inode);

	switch (whence) {
	case SEEK_SET:
		break;
	case SEEK_END:
		/* SEEK_END requires the OCFS2 inode lock for the file
		 * because it references the file's size.
		 */
		ret = ocfs2_inode_lock(inode, NULL, 0);
		if (ret < 0) {
			mlog_errno(ret);
			goto out;
		}
		offset += i_size_read(inode);
		ocfs2_inode_unlock(inode, 0);
		break;
	case SEEK_CUR:
		if (offset == 0) {
			offset = file->f_pos;
			goto out;
		}
		offset += file->f_pos;
		break;
	case SEEK_DATA:
	case SEEK_HOLE:
		ret = ocfs2_seek_data_hole_offset(file, &offset, whence);
		if (ret)
			goto out;
		break;
	default:
		ret = -EINVAL;
		goto out;
	}

	offset = vfs_setpos(file, offset, inode->i_sb->s_maxbytes);

out:
	inode_unlock(inode);
	if (ret)
		return ret;
	return offset;
}