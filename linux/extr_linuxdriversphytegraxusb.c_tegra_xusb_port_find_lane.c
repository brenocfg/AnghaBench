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
struct tegra_xusb_port {scalar_t__ index; int /*<<< orphan*/  dev; int /*<<< orphan*/  padctl; } ;
struct tegra_xusb_lane_map {scalar_t__ port; int /*<<< orphan*/  index; scalar_t__ type; } ;
struct tegra_xusb_lane {TYPE_1__* soc; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct tegra_xusb_lane* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct tegra_xusb_lane*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_xusb_lane* tegra_xusb_find_lane (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_xusb_lane_check (struct tegra_xusb_lane*,char const*) ; 

struct tegra_xusb_lane *
tegra_xusb_port_find_lane(struct tegra_xusb_port *port,
			  const struct tegra_xusb_lane_map *map,
			  const char *function)
{
	struct tegra_xusb_lane *lane, *match = ERR_PTR(-ENODEV);

	for (; map->type; map++) {
		if (port->index != map->port)
			continue;

		lane = tegra_xusb_find_lane(port->padctl, map->type,
					    map->index);
		if (IS_ERR(lane))
			continue;

		if (!tegra_xusb_lane_check(lane, function))
			continue;

		if (!IS_ERR(match))
			dev_err(&port->dev, "conflicting match: %s-%u / %s\n",
				map->type, map->index, match->soc->name);
		else
			match = lane;
	}

	return match;
}