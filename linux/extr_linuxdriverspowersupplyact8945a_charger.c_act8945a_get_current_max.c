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
struct regmap {int dummy; } ;
struct act8945a_charger {int /*<<< orphan*/  chglev_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACT8945A_APCH_STATE ; 
 int /*<<< orphan*/  ACT8945A_APCH_STATUS ; 
 unsigned int APCH_STATE_ACINSTAT ; 
 unsigned int APCH_STATE_CSTATE ; 
#define  APCH_STATE_CSTATE_DISABLED 131 
#define  APCH_STATE_CSTATE_EOC 130 
#define  APCH_STATE_CSTATE_FAST 129 
#define  APCH_STATE_CSTATE_PRE 128 
 unsigned int APCH_STATE_CSTATE_SHIFT ; 
 int MAX_CURRENT_AC_HIGH ; 
 int MAX_CURRENT_AC_HIGH_PRE ; 
 int MAX_CURRENT_AC_LOW ; 
 int MAX_CURRENT_AC_LOW_PRE ; 
 int MAX_CURRENT_USB_HIGH ; 
 int MAX_CURRENT_USB_LOW ; 
 int MAX_CURRENT_USB_PRE ; 
 int gpiod_get_value (int /*<<< orphan*/ ) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int act8945a_get_current_max(struct act8945a_charger *charger,
				    struct regmap *regmap, int *val)
{
	int ret;
	unsigned int status, state;
	unsigned int acin_state;
	int chgin_level = gpiod_get_value(charger->chglev_gpio);

	ret = regmap_read(regmap, ACT8945A_APCH_STATUS, &status);
	if (ret < 0)
		return ret;

	ret = regmap_read(regmap, ACT8945A_APCH_STATE, &state);
	if (ret < 0)
		return ret;

	acin_state = (state & APCH_STATE_ACINSTAT) >> 1;

	state &= APCH_STATE_CSTATE;
	state >>= APCH_STATE_CSTATE_SHIFT;

	switch (state) {
	case APCH_STATE_CSTATE_PRE:
		if (acin_state) {
			if (chgin_level)
				*val = MAX_CURRENT_AC_HIGH_PRE;
			else
				*val = MAX_CURRENT_AC_LOW_PRE;
		} else {
			*val = MAX_CURRENT_USB_PRE;
		}
		break;
	case APCH_STATE_CSTATE_FAST:
		if (acin_state) {
			if (chgin_level)
				*val = MAX_CURRENT_AC_HIGH;
			else
				*val = MAX_CURRENT_AC_LOW;
		} else {
			if (chgin_level)
				*val = MAX_CURRENT_USB_HIGH;
			else
				*val = MAX_CURRENT_USB_LOW;
		}
		break;
	case APCH_STATE_CSTATE_EOC:
	case APCH_STATE_CSTATE_DISABLED:
	default:
		*val = 0;
		break;
	}

	return 0;
}