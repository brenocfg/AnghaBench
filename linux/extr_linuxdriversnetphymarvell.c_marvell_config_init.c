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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  marvell_config_led (struct phy_device*) ; 
 int marvell_of_reg_init (struct phy_device*) ; 

__attribute__((used)) static int marvell_config_init(struct phy_device *phydev)
{
	/* Set defalut LED */
	marvell_config_led(phydev);

	/* Set registers from marvell,reg-init DT property */
	return marvell_of_reg_init(phydev);
}