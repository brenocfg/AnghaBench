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
struct max77620_pctrl_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  rmap; } ;

/* Variables and functions */
 unsigned int MAX77620_FPS_SRC_MASK ; 
 unsigned int MAX77620_FPS_SRC_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

__attribute__((used)) static int max77620_get_default_fps(struct max77620_pctrl_info *mpci,
				    int addr, int *fps)
{
	unsigned int val;
	int ret;

	ret = regmap_read(mpci->rmap, addr, &val);
	if (ret < 0) {
		dev_err(mpci->dev, "Reg PUE_GPIO read failed: %d\n", ret);
		return ret;
	}
	*fps = (val & MAX77620_FPS_SRC_MASK) >> MAX77620_FPS_SRC_SHIFT;

	return 0;
}