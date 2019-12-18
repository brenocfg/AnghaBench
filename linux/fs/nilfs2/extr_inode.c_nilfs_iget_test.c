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
struct nilfs_inode_info {scalar_t__ i_root; scalar_t__ i_cno; int /*<<< orphan*/  i_state; } ;
struct nilfs_iget_args {scalar_t__ ino; scalar_t__ root; scalar_t__ cno; scalar_t__ for_gc; } ;
struct inode {scalar_t__ i_ino; } ;

/* Variables and functions */
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 int /*<<< orphan*/  NILFS_I_GCINODE ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_iget_test(struct inode *inode, void *opaque)
{
	struct nilfs_iget_args *args = opaque;
	struct nilfs_inode_info *ii;

	if (args->ino != inode->i_ino || args->root != NILFS_I(inode)->i_root)
		return 0;

	ii = NILFS_I(inode);
	if (!test_bit(NILFS_I_GCINODE, &ii->i_state))
		return !args->for_gc;

	return args->for_gc && args->cno == ii->i_cno;
}