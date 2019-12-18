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
struct nilfs_root {int dummy; } ;
struct nilfs_iget_args {unsigned long ino; int /*<<< orphan*/  for_gc; int /*<<< orphan*/  cno; struct nilfs_root* root; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int insert_inode_locked4 (struct inode*,unsigned long,int /*<<< orphan*/ ,struct nilfs_iget_args*) ; 
 int /*<<< orphan*/  nilfs_iget_test ; 

__attribute__((used)) static int nilfs_insert_inode_locked(struct inode *inode,
				     struct nilfs_root *root,
				     unsigned long ino)
{
	struct nilfs_iget_args args = {
		.ino = ino, .root = root, .cno = 0, .for_gc = 0
	};

	return insert_inode_locked4(inode, ino, nilfs_iget_test, &args);
}