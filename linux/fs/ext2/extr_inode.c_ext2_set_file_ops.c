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
struct inode {TYPE_1__* i_mapping; int /*<<< orphan*/  i_sb; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 scalar_t__ IS_DAX (struct inode*) ; 
 int /*<<< orphan*/  NOBH ; 
 int /*<<< orphan*/  ext2_aops ; 
 int /*<<< orphan*/  ext2_dax_aops ; 
 int /*<<< orphan*/  ext2_file_inode_operations ; 
 int /*<<< orphan*/  ext2_file_operations ; 
 int /*<<< orphan*/  ext2_nobh_aops ; 
 scalar_t__ test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ext2_set_file_ops(struct inode *inode)
{
	inode->i_op = &ext2_file_inode_operations;
	inode->i_fop = &ext2_file_operations;
	if (IS_DAX(inode))
		inode->i_mapping->a_ops = &ext2_dax_aops;
	else if (test_opt(inode->i_sb, NOBH))
		inode->i_mapping->a_ops = &ext2_nobh_aops;
	else
		inode->i_mapping->a_ops = &ext2_aops;
}