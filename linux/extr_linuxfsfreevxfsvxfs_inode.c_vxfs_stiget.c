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
struct super_block {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_2__ {int /*<<< orphan*/  vsi_stilist; } ;

/* Variables and functions */
 int /*<<< orphan*/  VXFS_INO (struct inode*) ; 
 TYPE_1__* VXFS_SBI (struct super_block*) ; 
 int __vxfs_iget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_next_ino () ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct inode* new_inode (struct super_block*) ; 

struct inode *
vxfs_stiget(struct super_block *sbp, ino_t ino)
{
	struct inode *inode;
	int error;

	inode = new_inode(sbp);
	if (!inode)
		return NULL;
	inode->i_ino = get_next_ino();

	error = __vxfs_iget(VXFS_SBI(sbp)->vsi_stilist, VXFS_INO(inode), ino);
	if (error) {
		iput(inode);
		return NULL;
	}

	return inode;
}