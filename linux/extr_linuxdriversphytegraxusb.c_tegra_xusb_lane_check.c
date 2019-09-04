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
struct tegra_xusb_lane {size_t function; TYPE_1__* soc; } ;
struct TYPE_2__ {char** funcs; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static bool tegra_xusb_lane_check(struct tegra_xusb_lane *lane,
				  const char *function)
{
	const char *func = lane->soc->funcs[lane->function];

	return strcmp(function, func) == 0;
}