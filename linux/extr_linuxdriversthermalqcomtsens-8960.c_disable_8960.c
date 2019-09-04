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
struct tsens_device {int num_sensors; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNTL_ADDR ; 
 int /*<<< orphan*/  EN ; 
 int /*<<< orphan*/  GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SENSOR0_SHIFT ; 
 int /*<<< orphan*/  SLP_CLK_ENA ; 
 int /*<<< orphan*/  SLP_CLK_ENA_8660 ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_8960(struct tsens_device *tmdev)
{
	int ret;
	u32 reg_cntl;
	u32 mask;

	mask = GENMASK(tmdev->num_sensors - 1, 0);
	mask <<= SENSOR0_SHIFT;
	mask |= EN;

	ret = regmap_read(tmdev->map, CNTL_ADDR, &reg_cntl);
	if (ret)
		return;

	reg_cntl &= ~mask;

	if (tmdev->num_sensors > 1)
		reg_cntl &= ~SLP_CLK_ENA;
	else
		reg_cntl &= ~SLP_CLK_ENA_8660;

	regmap_write(tmdev->map, CNTL_ADDR, reg_cntl);
}