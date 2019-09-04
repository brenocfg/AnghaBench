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
struct axp20x_dev {int variant; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
#define  AXP803_DCDC3 135 
#define  AXP803_DCDC6 134 
#define  AXP803_ID 133 
 int /*<<< orphan*/  AXP803_POLYPHASE_CTRL ; 
#define  AXP806_DCDCB 132 
#define  AXP806_DCDCC 131 
#define  AXP806_DCDCE 130 
 int /*<<< orphan*/  AXP806_DCDC_MODE_CTRL2 ; 
#define  AXP806_ID 129 
#define  AXP813_ID 128 
 int BIT (int) ; 
 int GENMASK (int,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool axp20x_is_polyphase_slave(struct axp20x_dev *axp20x, int id)
{
	u32 reg = 0;

	/*
	 * Currently in our supported AXP variants, only AXP803, AXP806,
	 * and AXP813 have polyphase regulators.
	 */
	switch (axp20x->variant) {
	case AXP803_ID:
	case AXP813_ID:
		regmap_read(axp20x->regmap, AXP803_POLYPHASE_CTRL, &reg);

		switch (id) {
		case AXP803_DCDC3:
			return !!(reg & BIT(6));
		case AXP803_DCDC6:
			return !!(reg & BIT(5));
		}
		break;

	case AXP806_ID:
		regmap_read(axp20x->regmap, AXP806_DCDC_MODE_CTRL2, &reg);

		switch (id) {
		case AXP806_DCDCB:
			return (((reg & GENMASK(7, 6)) == BIT(6)) ||
				((reg & GENMASK(7, 6)) == BIT(7)));
		case AXP806_DCDCC:
			return ((reg & GENMASK(7, 6)) == BIT(7));
		case AXP806_DCDCE:
			return !!(reg & BIT(5));
		}
		break;

	default:
		return false;
	}

	return false;
}