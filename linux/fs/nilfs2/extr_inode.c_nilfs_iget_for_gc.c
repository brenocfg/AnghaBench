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
struct nilfs_iget_args {unsigned long ino; int for_gc; int /*<<< orphan*/  cno; int /*<<< orphan*/ * root; } ;
struct inode {int i_state; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int ENOMEM ; 
 struct inode* ERR_PTR (int) ; 
 int I_NEW ; 
 struct inode* iget5_locked (struct super_block*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nilfs_iget_args*) ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 int /*<<< orphan*/  nilfs_iget_set ; 
 int /*<<< orphan*/  nilfs_iget_test ; 
 int nilfs_init_gcinode (struct inode*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *nilfs_iget_for_gc(struct super_block *sb, unsigned long ino,
				__u64 cno)
{
	struct nilfs_iget_args args = {
		.ino = ino, .root = NULL, .cno = cno, .for_gc = 1
	};
	struct inode *inode;
	int err;

	inode = iget5_locked(sb, ino, nilfs_iget_test, nilfs_iget_set, &args);
	if (unlikely(!inode))
		return ERR_PTR(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		return inode;

	err = nilfs_init_gcinode(inode);
	if (unlikely(err)) {
		iget_failed(inode);
		return ERR_PTR(err);
	}
	unlock_new_inode(inode);
	return inode;
}