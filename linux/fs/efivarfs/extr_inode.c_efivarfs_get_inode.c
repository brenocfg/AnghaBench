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
struct super_block {int dummy; } ;
struct inode {int i_mode; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_ino; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
#define  S_IFDIR 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int /*<<< orphan*/  S_IMMUTABLE ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  efivarfs_dir_inode_operations ; 
 int /*<<< orphan*/  efivarfs_file_operations ; 
 int /*<<< orphan*/  get_next_ino () ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  simple_dir_operations ; 

struct inode *efivarfs_get_inode(struct super_block *sb,
				const struct inode *dir, int mode,
				dev_t dev, bool is_removable)
{
	struct inode *inode = new_inode(sb);

	if (inode) {
		inode->i_ino = get_next_ino();
		inode->i_mode = mode;
		inode->i_atime = inode->i_mtime = inode->i_ctime = current_time(inode);
		inode->i_flags = is_removable ? 0 : S_IMMUTABLE;
		switch (mode & S_IFMT) {
		case S_IFREG:
			inode->i_fop = &efivarfs_file_operations;
			break;
		case S_IFDIR:
			inode->i_op = &efivarfs_dir_inode_operations;
			inode->i_fop = &simple_dir_operations;
			inc_nlink(inode);
			break;
		}
	}
	return inode;
}