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
struct smb347_charger {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_FULL ; 
 int POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 int /*<<< orphan*/  STAT_C ; 
 unsigned int STAT_C_CHARGER_ERROR ; 
 unsigned int STAT_C_CHG_MASK ; 
 unsigned int STAT_C_CHG_SHIFT ; 
 unsigned int STAT_C_CHG_TERM ; 
 unsigned int STAT_C_HOLDOFF_STAT ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  smb347_is_ps_online (struct smb347_charger*) ; 

__attribute__((used)) static int smb347_get_charging_status(struct smb347_charger *smb)
{
	int ret, status;
	unsigned int val;

	if (!smb347_is_ps_online(smb))
		return POWER_SUPPLY_STATUS_DISCHARGING;

	ret = regmap_read(smb->regmap, STAT_C, &val);
	if (ret < 0)
		return ret;

	if ((val & STAT_C_CHARGER_ERROR) ||
			(val & STAT_C_HOLDOFF_STAT)) {
		/*
		 * set to NOT CHARGING upon charger error
		 * or charging has stopped.
		 */
		status = POWER_SUPPLY_STATUS_NOT_CHARGING;
	} else {
		if ((val & STAT_C_CHG_MASK) >> STAT_C_CHG_SHIFT) {
			/*
			 * set to charging if battery is in pre-charge,
			 * fast charge or taper charging mode.
			 */
			status = POWER_SUPPLY_STATUS_CHARGING;
		} else if (val & STAT_C_CHG_TERM) {
			/*
			 * set the status to FULL if battery is not in pre
			 * charge, fast charge or taper charging mode AND
			 * charging is terminated at least once.
			 */
			status = POWER_SUPPLY_STATUS_FULL;
		} else {
			/*
			 * in this case no charger error or termination
			 * occured but charging is not in progress!!!
			 */
			status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		}
	}

	return status;
}