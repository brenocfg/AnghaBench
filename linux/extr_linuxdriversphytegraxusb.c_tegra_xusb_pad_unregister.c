#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tegra_xusb_pad {int /*<<< orphan*/  dev; int /*<<< orphan*/ * lanes; int /*<<< orphan*/  provider; TYPE_1__* soc; } ;
struct TYPE_2__ {unsigned int num_lanes; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_phy_provider_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_xusb_lane_destroy (int /*<<< orphan*/ ) ; 

void tegra_xusb_pad_unregister(struct tegra_xusb_pad *pad)
{
	unsigned int i = pad->soc->num_lanes;

	of_phy_provider_unregister(pad->provider);

	while (i--)
		tegra_xusb_lane_destroy(pad->lanes[i]);

	device_unregister(&pad->dev);
}