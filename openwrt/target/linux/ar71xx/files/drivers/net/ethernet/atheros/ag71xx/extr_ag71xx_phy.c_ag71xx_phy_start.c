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
struct ag71xx_platform_data {scalar_t__ switch_data; scalar_t__ mii_bus_dev; } ;
struct ag71xx {int link; scalar_t__ phy_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ag71xx_ar7240_start (struct ag71xx*) ; 
 struct ag71xx_platform_data* ag71xx_get_pdata (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_link_adjust (struct ag71xx*) ; 
 int /*<<< orphan*/  phy_start (scalar_t__) ; 

void ag71xx_phy_start(struct ag71xx *ag)
{
	struct ag71xx_platform_data *pdata = ag71xx_get_pdata(ag);

	if (ag->phy_dev) {
		phy_start(ag->phy_dev);
	} else if (pdata->mii_bus_dev && pdata->switch_data) {
		ag71xx_ar7240_start(ag);
	} else {
		ag->link = 1;
		ag71xx_link_adjust(ag);
	}
}