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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OVL_UPPERDATA ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  ovl_open_flags_need_copy_up (int) ; 
 int /*<<< orphan*/  ovl_test_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool ovl_dentry_needs_data_copy_up_locked(struct dentry *dentry, int flags)
{
	if (!ovl_open_flags_need_copy_up(flags))
		return false;

	return !ovl_test_flag(OVL_UPPERDATA, d_inode(dentry));
}