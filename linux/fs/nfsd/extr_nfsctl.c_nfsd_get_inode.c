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
typedef  int umode_t ;
struct super_block {int dummy; } ;
struct inode {int i_mode; int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD_MaxReserved ; 
#define  S_IFDIR 128 
 int S_IFMT ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  iunique (struct super_block*,int /*<<< orphan*/ ) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  simple_dir_inode_operations ; 
 int /*<<< orphan*/  simple_dir_operations ; 

__attribute__((used)) static struct inode *nfsd_get_inode(struct super_block *sb, umode_t mode)
{
	struct inode *inode = new_inode(sb);
	if (!inode)
		return NULL;
	/* Following advice from simple_fill_super documentation: */
	inode->i_ino = iunique(sb, NFSD_MaxReserved);
	inode->i_mode = mode;
	inode->i_atime = inode->i_mtime = inode->i_ctime = current_time(inode);
	switch (mode & S_IFMT) {
	case S_IFDIR:
		inode->i_fop = &simple_dir_operations;
		inode->i_op = &simple_dir_inode_operations;
		inc_nlink(inode);
	default:
		break;
	}
	return inode;
}