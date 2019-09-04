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
union power_supply_propval {int intval; } ;
typedef  int /*<<< orphan*/  u8 ;
struct adp5061_state {int dummy; } ;

/* Variables and functions */
 int ADP5061_CHG_FAST_CV ; 
 size_t ADP5061_CHG_STATUS_1_CHG_STATUS (int /*<<< orphan*/ ) ; 
 int POWER_SUPPLY_STATUS_UNKNOWN ; 
 int* adp5061_chg_type ; 
 int adp5061_get_status (struct adp5061_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adp5061_get_chg_type(struct adp5061_state *st,
				union power_supply_propval *val)
{
	u8 status1, status2;
	int chg_type, ret;

	ret = adp5061_get_status(st, &status1, &status2);
	if (ret < 0)
		return ret;

	chg_type = adp5061_chg_type[ADP5061_CHG_STATUS_1_CHG_STATUS(status1)];
	if (chg_type > ADP5061_CHG_FAST_CV)
		val->intval = POWER_SUPPLY_STATUS_UNKNOWN;
	else
		val->intval = chg_type;

	return ret;
}