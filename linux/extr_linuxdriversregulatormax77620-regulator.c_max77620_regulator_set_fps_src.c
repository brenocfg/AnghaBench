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
struct max77620_regulator_info {int fps_addr; } ;
struct max77620_regulator {int* active_fps_src; int /*<<< orphan*/  dev; int /*<<< orphan*/  rmap; struct max77620_regulator_info** rinfo; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MAX77620_FPS_SRC_0 132 
#define  MAX77620_FPS_SRC_1 131 
#define  MAX77620_FPS_SRC_2 130 
#define  MAX77620_FPS_SRC_DEF 129 
 unsigned int MAX77620_FPS_SRC_MASK ; 
#define  MAX77620_FPS_SRC_NONE 128 
 unsigned int MAX77620_FPS_SRC_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,unsigned int,int) ; 

__attribute__((used)) static int max77620_regulator_set_fps_src(struct max77620_regulator *pmic,
					  int fps_src, int id)
{
	struct max77620_regulator_info *rinfo = pmic->rinfo[id];
	unsigned int val;
	int ret;

	if (!rinfo)
		return 0;

	switch (fps_src) {
	case MAX77620_FPS_SRC_0:
	case MAX77620_FPS_SRC_1:
	case MAX77620_FPS_SRC_2:
	case MAX77620_FPS_SRC_NONE:
		break;

	case MAX77620_FPS_SRC_DEF:
		ret = regmap_read(pmic->rmap, rinfo->fps_addr, &val);
		if (ret < 0) {
			dev_err(pmic->dev, "Reg 0x%02x read failed %d\n",
				rinfo->fps_addr, ret);
			return ret;
		}
		ret = (val & MAX77620_FPS_SRC_MASK) >> MAX77620_FPS_SRC_SHIFT;
		pmic->active_fps_src[id] = ret;
		return 0;

	default:
		dev_err(pmic->dev, "Invalid FPS %d for regulator %d\n",
			fps_src, id);
		return -EINVAL;
	}

	ret = regmap_update_bits(pmic->rmap, rinfo->fps_addr,
				 MAX77620_FPS_SRC_MASK,
				 fps_src << MAX77620_FPS_SRC_SHIFT);
	if (ret < 0) {
		dev_err(pmic->dev, "Reg 0x%02x update failed %d\n",
			rinfo->fps_addr, ret);
		return ret;
	}
	pmic->active_fps_src[id] = fps_src;

	return 0;
}