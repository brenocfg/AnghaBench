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
struct velocity_info {int /*<<< orphan*/  mac_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMCR_ANENABLE ; 
 int /*<<< orphan*/  BMCR_ANRESTART ; 
 int /*<<< orphan*/  MII_BMCR ; 
 scalar_t__ MII_REG_BITS_IS_ON (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MII_REG_BITS_ON (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mii_set_auto_on(struct velocity_info *vptr)
{
	if (MII_REG_BITS_IS_ON(BMCR_ANENABLE, MII_BMCR, vptr->mac_regs))
		MII_REG_BITS_ON(BMCR_ANRESTART, MII_BMCR, vptr->mac_regs);
	else
		MII_REG_BITS_ON(BMCR_ANENABLE, MII_BMCR, vptr->mac_regs);
}