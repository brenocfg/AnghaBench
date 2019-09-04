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
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OVL_UPPERDATA ; 
 int /*<<< orphan*/  ovl_should_check_upperdata (struct inode*) ; 
 int /*<<< orphan*/  ovl_test_flag (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  smp_rmb () ; 

bool ovl_has_upperdata(struct inode *inode)
{
	if (!ovl_should_check_upperdata(inode))
		return true;

	if (!ovl_test_flag(OVL_UPPERDATA, inode))
		return false;
	/*
	 * Pairs with smp_wmb() in ovl_set_upperdata(). Main user of
	 * ovl_has_upperdata() is ovl_copy_up_meta_inode_data(). Make sure
	 * if setting of OVL_UPPERDATA is visible, then effects of writes
	 * before that are visible too.
	 */
	smp_rmb();
	return true;
}