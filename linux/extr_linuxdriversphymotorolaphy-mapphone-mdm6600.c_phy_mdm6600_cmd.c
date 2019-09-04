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
struct phy_mdm6600 {TYPE_1__* cmd_gpios; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int BIT (int) ; 
 int PHY_MDM6600_NR_CMD_LINES ; 
 int /*<<< orphan*/  gpiod_set_array_value_cansleep (int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void phy_mdm6600_cmd(struct phy_mdm6600 *ddata, int val)
{
	int values[PHY_MDM6600_NR_CMD_LINES];
	int i;

	val &= (1 << PHY_MDM6600_NR_CMD_LINES) - 1;
	for (i = 0; i < PHY_MDM6600_NR_CMD_LINES; i++)
		values[i] = (val & BIT(i)) >> i;

	gpiod_set_array_value_cansleep(PHY_MDM6600_NR_CMD_LINES,
				       ddata->cmd_gpios->desc, values);
}