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
typedef  int u32 ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ32K_CFG2 ; 
 int /*<<< orphan*/  BQ32K_TCH2 ; 
 int EINVAL ; 
 int bq32k_write (struct device*,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int trickle_charger_of_init(struct device *dev, struct device_node *node)
{
	unsigned char reg;
	int error;
	u32 ohms = 0;

	if (of_property_read_u32(node, "trickle-resistor-ohms" , &ohms))
		return 0;

	switch (ohms) {
	case 180+940:
		/*
		 * TCHE[3:0] == 0x05, TCH2 == 1, TCFE == 0 (charging
		 * over diode and 940ohm resistor)
		 */

		if (of_property_read_bool(node, "trickle-diode-disable")) {
			dev_err(dev, "diode and resistor mismatch\n");
			return -EINVAL;
		}
		reg = 0x05;
		break;

	case 180+20000:
		/* diode disabled */

		if (!of_property_read_bool(node, "trickle-diode-disable")) {
			dev_err(dev, "bq32k: diode and resistor mismatch\n");
			return -EINVAL;
		}
		reg = 0x45;
		break;

	default:
		dev_err(dev, "invalid resistor value (%d)\n", ohms);
		return -EINVAL;
	}

	error = bq32k_write(dev, &reg, BQ32K_CFG2, 1);
	if (error)
		return error;

	reg = 0x20;
	error = bq32k_write(dev, &reg, BQ32K_TCH2, 1);
	if (error)
		return error;

	dev_info(dev, "Enabled trickle RTC battery charge.\n");
	return 0;
}