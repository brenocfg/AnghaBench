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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_ANY_ID ; 
 int phy_unregister_fixup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int phy_unregister_fixup_for_uid(u32 phy_uid, u32 phy_uid_mask)
{
	return phy_unregister_fixup(PHY_ANY_ID, phy_uid, phy_uid_mask);
}