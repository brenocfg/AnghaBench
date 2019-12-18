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
 int /*<<< orphan*/  ovl_set_flag (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  smp_wmb () ; 

void ovl_set_upperdata(struct inode *inode)
{
	/*
	 * Pairs with smp_rmb() in ovl_has_upperdata(). Make sure
	 * if OVL_UPPERDATA flag is visible, then effects of write operations
	 * before it are visible as well.
	 */
	smp_wmb();
	ovl_set_flag(OVL_UPPERDATA, inode);
}