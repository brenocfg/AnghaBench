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
struct max8925_power_info {int bat_online; int ac_online; int topoff_threshold; int fast_charge; int /*<<< orphan*/  gpm; scalar_t__ batt_detect; scalar_t__ usb_online; int /*<<< orphan*/  no_temp_support; int /*<<< orphan*/  no_insert_detect; } ;
struct max8925_chip {int dummy; } ;

/* Variables and functions */
 int MAX8925_CHG_AC_RANGE_MASK ; 
 int /*<<< orphan*/  MAX8925_CHG_CNTL1 ; 
 int MAX8925_CHG_MBDET ; 
 int /*<<< orphan*/  MAX8925_CHG_STATUS ; 
 int /*<<< orphan*/  MAX8925_IRQ_VCHG_DC_F ; 
 int /*<<< orphan*/  MAX8925_IRQ_VCHG_DC_OVP ; 
 int /*<<< orphan*/  MAX8925_IRQ_VCHG_DC_R ; 
 int /*<<< orphan*/  MAX8925_IRQ_VCHG_DONE ; 
 int /*<<< orphan*/  MAX8925_IRQ_VCHG_RST ; 
 int /*<<< orphan*/  MAX8925_IRQ_VCHG_SYSLOW_F ; 
 int /*<<< orphan*/  MAX8925_IRQ_VCHG_SYSLOW_R ; 
 int /*<<< orphan*/  MAX8925_IRQ_VCHG_THM_OK_F ; 
 int /*<<< orphan*/  MAX8925_IRQ_VCHG_THM_OK_R ; 
 int /*<<< orphan*/  MAX8925_IRQ_VCHG_TMR_FAULT ; 
 int /*<<< orphan*/  MAX8925_IRQ_VCHG_TOPOFF ; 
 int /*<<< orphan*/  MEASURE_VCHG ; 
 int /*<<< orphan*/  REQUEST_IRQ (int /*<<< orphan*/ ,char*) ; 
 int max8925_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max8925_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int start_measure (struct max8925_power_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max8925_init_charger(struct max8925_chip *chip,
					  struct max8925_power_info *info)
{
	int ret;

	REQUEST_IRQ(MAX8925_IRQ_VCHG_DC_OVP, "ac-ovp");
	if (!info->no_insert_detect) {
		REQUEST_IRQ(MAX8925_IRQ_VCHG_DC_F, "ac-remove");
		REQUEST_IRQ(MAX8925_IRQ_VCHG_DC_R, "ac-insert");
	}
	if (!info->no_temp_support) {
		REQUEST_IRQ(MAX8925_IRQ_VCHG_THM_OK_R, "batt-temp-in-range");
		REQUEST_IRQ(MAX8925_IRQ_VCHG_THM_OK_F, "batt-temp-out-range");
	}
	REQUEST_IRQ(MAX8925_IRQ_VCHG_SYSLOW_F, "vsys-high");
	REQUEST_IRQ(MAX8925_IRQ_VCHG_SYSLOW_R, "vsys-low");
	REQUEST_IRQ(MAX8925_IRQ_VCHG_RST, "charger-reset");
	REQUEST_IRQ(MAX8925_IRQ_VCHG_DONE, "charger-done");
	REQUEST_IRQ(MAX8925_IRQ_VCHG_TOPOFF, "charger-topoff");
	REQUEST_IRQ(MAX8925_IRQ_VCHG_TMR_FAULT, "charger-timer-expire");

	info->usb_online = 0;
	info->bat_online = 0;

	/* check for power - can miss interrupt at boot time */
	if (start_measure(info, MEASURE_VCHG) * 2000 > 500000)
		info->ac_online = 1;
	else
		info->ac_online = 0;

	ret = max8925_reg_read(info->gpm, MAX8925_CHG_STATUS);
	if (ret >= 0) {
		/*
		 * If battery detection is enabled, ID pin of battery is
		 * connected to MBDET pin of MAX8925. It could be used to
		 * detect battery presence.
		 * Otherwise, we have to assume that battery is always on.
		 */
		if (info->batt_detect)
			info->bat_online = (ret & MAX8925_CHG_MBDET) ? 0 : 1;
		else
			info->bat_online = 1;
		if (ret & MAX8925_CHG_AC_RANGE_MASK)
			info->ac_online = 1;
		else
			info->ac_online = 0;
	}
	/* disable charge */
	max8925_set_bits(info->gpm, MAX8925_CHG_CNTL1, 1 << 7, 1 << 7);
	/* set charging current in charge topoff mode */
	max8925_set_bits(info->gpm, MAX8925_CHG_CNTL1, 3 << 5,
			 info->topoff_threshold << 5);
	/* set charing current in fast charge mode */
	max8925_set_bits(info->gpm, MAX8925_CHG_CNTL1, 7, info->fast_charge);

	return 0;
}