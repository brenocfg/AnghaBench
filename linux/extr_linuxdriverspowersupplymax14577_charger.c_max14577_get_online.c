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
typedef  int u8 ;
struct regmap {int dummy; } ;
struct max14577_charger {TYPE_1__* max14577; } ;
typedef  enum max14577_muic_charger_type { ____Placeholder_max14577_muic_charger_type } max14577_muic_charger_type ;
struct TYPE_2__ {int /*<<< orphan*/  dev_type; struct regmap* regmap; } ;

/* Variables and functions */
#define  MAX14577_CHARGER_TYPE_DEAD_BATTERY 137 
#define  MAX14577_CHARGER_TYPE_DEDICATED_CHG 136 
#define  MAX14577_CHARGER_TYPE_DOWNSTREAM_PORT 135 
#define  MAX14577_CHARGER_TYPE_NONE 134 
#define  MAX14577_CHARGER_TYPE_RESERVED 133 
#define  MAX14577_CHARGER_TYPE_SPECIAL_1A 132 
#define  MAX14577_CHARGER_TYPE_SPECIAL_500MA 131 
#define  MAX14577_CHARGER_TYPE_USB 130 
 int /*<<< orphan*/  MAX14577_MUIC_REG_STATUS2 ; 
#define  MAX77836_CHARGER_TYPE_RESERVED 129 
#define  MAX77836_CHARGER_TYPE_SPECIAL_BIAS 128 
 int STATUS2_CHGTYP_MASK ; 
 int STATUS2_CHGTYP_SHIFT ; 
 int max14577_read_reg (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 int maxim_get_charger_type (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max14577_get_online(struct max14577_charger *chg, int *val)
{
	struct regmap *rmap = chg->max14577->regmap;
	u8 reg_data;
	int ret;
	enum max14577_muic_charger_type chg_type;

	ret = max14577_read_reg(rmap, MAX14577_MUIC_REG_STATUS2, &reg_data);
	if (ret < 0)
		return ret;

	reg_data = ((reg_data & STATUS2_CHGTYP_MASK) >> STATUS2_CHGTYP_SHIFT);
	chg_type = maxim_get_charger_type(chg->max14577->dev_type, reg_data);
	switch (chg_type) {
	case MAX14577_CHARGER_TYPE_USB:
	case MAX14577_CHARGER_TYPE_DEDICATED_CHG:
	case MAX14577_CHARGER_TYPE_SPECIAL_500MA:
	case MAX14577_CHARGER_TYPE_SPECIAL_1A:
	case MAX14577_CHARGER_TYPE_DEAD_BATTERY:
	case MAX77836_CHARGER_TYPE_SPECIAL_BIAS:
		*val = 1;
		break;
	case MAX14577_CHARGER_TYPE_NONE:
	case MAX14577_CHARGER_TYPE_DOWNSTREAM_PORT:
	case MAX14577_CHARGER_TYPE_RESERVED:
	case MAX77836_CHARGER_TYPE_RESERVED:
	default:
		*val = 0;
	}

	return 0;
}