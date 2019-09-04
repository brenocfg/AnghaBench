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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_thermctl_zone {TYPE_1__* sg; int /*<<< orphan*/  reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  sensor_temp_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_GET_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int translate_temp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_thermctl_get_temp(void *data, int *out_temp)
{
	struct tegra_thermctl_zone *zone = data;
	u32 val;

	val = readl(zone->reg);
	val = REG_GET_MASK(val, zone->sg->sensor_temp_mask);
	*out_temp = translate_temp(val);

	return 0;
}