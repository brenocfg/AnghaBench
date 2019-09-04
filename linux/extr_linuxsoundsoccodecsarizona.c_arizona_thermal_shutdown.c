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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_INTERRUPT_RAW_STATUS_3 ; 
 int ARIZONA_OUT4L_ENA ; 
 int ARIZONA_OUT4R_ENA ; 
 int /*<<< orphan*/  ARIZONA_OUTPUT_ENABLES_1 ; 
 unsigned int ARIZONA_SPK_OVERHEAT_STS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t arizona_thermal_shutdown(int irq, void *data)
{
	struct arizona *arizona = data;
	unsigned int val;
	int ret;

	ret = regmap_read(arizona->regmap, ARIZONA_INTERRUPT_RAW_STATUS_3,
			  &val);
	if (ret != 0) {
		dev_err(arizona->dev, "Failed to read thermal status: %d\n",
			ret);
	} else if (val & ARIZONA_SPK_OVERHEAT_STS) {
		dev_crit(arizona->dev, "Thermal shutdown\n");
		ret = regmap_update_bits(arizona->regmap,
					 ARIZONA_OUTPUT_ENABLES_1,
					 ARIZONA_OUT4L_ENA |
					 ARIZONA_OUT4R_ENA, 0);
		if (ret != 0)
			dev_crit(arizona->dev,
				 "Failed to disable speaker outputs: %d\n",
				 ret);
	}

	return IRQ_HANDLED;
}