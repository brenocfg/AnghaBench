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
struct rtsx_chip {int int_reg; int need_reinit; int card_exist; } ;

/* Variables and functions */
 int MS_CARD ; 
 int MS_EXIST ; 
 int OC_PDCTL ; 
 int /*<<< orphan*/  RTSX_BIPR ; 
 int /*<<< orphan*/  RTSX_STAT_RUN ; 
 int SD_CARD ; 
 int SD_EXIST ; 
 int SSC_PDCTL ; 
 int XD_CARD ; 
 int XD_EXIST ; 
 int /*<<< orphan*/  do_reset_ms_card (struct rtsx_chip*) ; 
 int /*<<< orphan*/  do_reset_sd_card (struct rtsx_chip*) ; 
 int /*<<< orphan*/  do_reset_xd_card (struct rtsx_chip*) ; 
 int /*<<< orphan*/  release_ms_card (struct rtsx_chip*) ; 
 int /*<<< orphan*/  release_sd_card (struct rtsx_chip*) ; 
 int /*<<< orphan*/  release_sdio (struct rtsx_chip*) ; 
 int /*<<< orphan*/  release_xd_card (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_force_power_on (struct rtsx_chip*,int) ; 
 int rtsx_readl (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_reset_chip (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_set_stat (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_timeout (int) ; 

void rtsx_reinit_cards(struct rtsx_chip *chip, int reset_chip)
{
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	rtsx_force_power_on(chip, SSC_PDCTL | OC_PDCTL);

	if (reset_chip)
		rtsx_reset_chip(chip);

	chip->int_reg = rtsx_readl(chip, RTSX_BIPR);

	if ((chip->int_reg & SD_EXIST) && (chip->need_reinit & SD_CARD)) {
		release_sdio(chip);
		release_sd_card(chip);

		wait_timeout(100);

		chip->card_exist |= SD_CARD;
		do_reset_sd_card(chip);
	}

	if ((chip->int_reg & XD_EXIST) && (chip->need_reinit & XD_CARD)) {
		release_xd_card(chip);

		wait_timeout(100);

		chip->card_exist |= XD_CARD;
		do_reset_xd_card(chip);
	}

	if ((chip->int_reg & MS_EXIST) && (chip->need_reinit & MS_CARD)) {
		release_ms_card(chip);

		wait_timeout(100);

		chip->card_exist |= MS_CARD;
		do_reset_ms_card(chip);
	}

	chip->need_reinit = 0;
}