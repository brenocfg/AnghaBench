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
struct madera {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int MADERA_OUT4L_ENA ; 
 int MADERA_OUT4R_ENA ; 
 int /*<<< orphan*/  MADERA_OUTPUT_ENABLES_1 ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int madera_check_speaker_overheat (struct madera*,int*,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t madera_thermal_warn(int irq, void *data)
{
	struct madera *madera = data;
	bool warn, shutdown;
	int ret;

	ret = madera_check_speaker_overheat(madera, &warn, &shutdown);
	if (ret || shutdown) { /* for safety attempt to shutdown on error */
		dev_crit(madera->dev, "Thermal shutdown\n");
		ret = regmap_update_bits(madera->regmap,
					 MADERA_OUTPUT_ENABLES_1,
					 MADERA_OUT4L_ENA |
					 MADERA_OUT4R_ENA, 0);
		if (ret != 0)
			dev_crit(madera->dev,
				 "Failed to disable speaker outputs: %d\n",
				 ret);
	} else if (warn) {
		dev_alert(madera->dev, "Thermal warning\n");
	} else {
		dev_info(madera->dev, "Spurious thermal warning\n");
		return IRQ_NONE;
	}

	return IRQ_HANDLED;
}