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
struct rcar_gen3_chan {scalar_t__ vbus; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 struct rcar_gen3_chan* phy_get_drvdata (struct phy*) ; 
 int regulator_disable (scalar_t__) ; 

__attribute__((used)) static int rcar_gen3_phy_usb2_power_off(struct phy *p)
{
	struct rcar_gen3_chan *channel = phy_get_drvdata(p);
	int ret = 0;

	if (channel->vbus)
		ret = regulator_disable(channel->vbus);

	return ret;
}