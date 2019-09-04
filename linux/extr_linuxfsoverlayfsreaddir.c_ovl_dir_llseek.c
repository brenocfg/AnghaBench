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
struct ovl_dir_file {scalar_t__ cache; TYPE_1__* realfile; scalar_t__ is_real; } ;
struct file {int /*<<< orphan*/  f_pos; struct ovl_dir_file* private_data; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  f_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  SEEK_CUR 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_dir_reset (struct file*) ; 
 int /*<<< orphan*/  ovl_seek_cursor (struct ovl_dir_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_llseek (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static loff_t ovl_dir_llseek(struct file *file, loff_t offset, int origin)
{
	loff_t res;
	struct ovl_dir_file *od = file->private_data;

	inode_lock(file_inode(file));
	if (!file->f_pos)
		ovl_dir_reset(file);

	if (od->is_real) {
		res = vfs_llseek(od->realfile, offset, origin);
		file->f_pos = od->realfile->f_pos;
	} else {
		res = -EINVAL;

		switch (origin) {
		case SEEK_CUR:
			offset += file->f_pos;
			break;
		case SEEK_SET:
			break;
		default:
			goto out_unlock;
		}
		if (offset < 0)
			goto out_unlock;

		if (offset != file->f_pos) {
			file->f_pos = offset;
			if (od->cache)
				ovl_seek_cursor(od, offset);
		}
		res = offset;
	}
out_unlock:
	inode_unlock(file_inode(file));

	return res;
}