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
struct max77620_regulator_info {int /*<<< orphan*/  fps_addr; } ;
struct max77620_regulator {int /*<<< orphan*/  dev; int /*<<< orphan*/  rmap; struct max77620_regulator_info** rinfo; } ;

/* Variables and functions */
 unsigned int MAX77620_FPS_SRC_MASK ; 
 unsigned int MAX77620_FPS_SRC_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int max77620_regulator_get_fps_src(struct max77620_regulator *pmic,
					  int id)
{
	struct max77620_regulator_info *rinfo = pmic->rinfo[id];
	unsigned int val;
	int ret;

	ret = regmap_read(pmic->rmap, rinfo->fps_addr, &val);
	if (ret < 0) {
		dev_err(pmic->dev, "Reg 0x%02x read failed %d\n",
			rinfo->fps_addr, ret);
		return ret;
	}

	return (val & MAX77620_FPS_SRC_MASK) >> MAX77620_FPS_SRC_SHIFT;
}