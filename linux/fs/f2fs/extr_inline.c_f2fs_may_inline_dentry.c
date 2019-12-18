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
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  INLINE_DENTRY ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool f2fs_may_inline_dentry(struct inode *inode)
{
	if (!test_opt(F2FS_I_SB(inode), INLINE_DENTRY))
		return false;

	if (!S_ISDIR(inode->i_mode))
		return false;

	return true;
}