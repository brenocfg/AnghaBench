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
struct rtsx_chip {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void rtsx_manage_2lun_mode(struct rtsx_chip *chip)
{
#ifdef SUPPORT_OCP
	u8 sd_oc, ms_oc;

	sd_oc = chip->ocp_stat & (SD_OC_NOW | SD_OC_EVER);
	ms_oc = chip->ocp_stat & (MS_OC_NOW | MS_OC_EVER);

	if (sd_oc || ms_oc)
		dev_dbg(rtsx_dev(chip), "Over current, OCPSTAT is 0x%x\n",
			chip->ocp_stat);

	if (sd_oc && (chip->card_exist & SD_CARD)) {
		rtsx_write_register(chip, CARD_OE, SD_OUTPUT_EN, 0);
		card_power_off(chip, SD_CARD);
		chip->card_fail |= SD_CARD;
	}

	if (ms_oc && (chip->card_exist & MS_CARD)) {
		rtsx_write_register(chip, CARD_OE, MS_OUTPUT_EN, 0);
		card_power_off(chip, MS_CARD);
		chip->card_fail |= MS_CARD;
	}
#endif
}