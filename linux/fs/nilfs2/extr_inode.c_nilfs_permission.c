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
struct nilfs_root {scalar_t__ cno; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct nilfs_root* i_root; } ;

/* Variables and functions */
 int EROFS ; 
 int MAY_WRITE ; 
 scalar_t__ NILFS_CPTREE_CURRENT_CNO ; 
 TYPE_1__* NILFS_I (struct inode*) ; 
 int generic_permission (struct inode*,int) ; 

int nilfs_permission(struct inode *inode, int mask)
{
	struct nilfs_root *root = NILFS_I(inode)->i_root;

	if ((mask & MAY_WRITE) && root &&
	    root->cno != NILFS_CPTREE_CURRENT_CNO)
		return -EROFS; /* snapshot is not writable */

	return generic_permission(inode, mask);
}