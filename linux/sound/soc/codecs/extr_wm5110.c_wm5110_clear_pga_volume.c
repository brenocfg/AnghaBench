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
struct arizona {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ARIZONA_OUTPUT_PATH_CONFIG_1L ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static int wm5110_clear_pga_volume(struct arizona *arizona, int output)
{
	unsigned int reg = ARIZONA_OUTPUT_PATH_CONFIG_1L + output * 4;
	int ret;

	ret = regmap_write(arizona->regmap, reg, 0x80);
	if (ret)
		dev_err(arizona->dev, "Failed to clear PGA (0x%x): %d\n",
			reg, ret);

	return ret;
}