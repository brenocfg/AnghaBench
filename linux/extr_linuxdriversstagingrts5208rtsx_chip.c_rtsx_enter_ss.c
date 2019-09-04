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
typedef  int /*<<< orphan*/  u32 ;
struct rtsx_chip {int /*<<< orphan*/  phy_debug_mode; scalar_t__ auto_delink_en; scalar_t__ power_down_in_ss; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_INT ; 
 int /*<<< orphan*/  CHANGE_LINK_STATE ; 
 scalar_t__ CHECK_PID (struct rtsx_chip*,int) ; 
 scalar_t__ CHK_SDIO_EXIST (struct rtsx_chip*) ; 
 int /*<<< orphan*/  HOST_SLEEP_STATE ; 
 int /*<<< orphan*/  IRQSTAT0 ; 
 int LINK_RDY_INT ; 
 int OC_PDCTL ; 
 int /*<<< orphan*/  RTSX_BIER ; 
 int /*<<< orphan*/  RTSX_CLR_DELINK (struct rtsx_chip*) ; 
 int /*<<< orphan*/  RTSX_STAT_SS ; 
 int SSC_PDCTL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_enter_L1 (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_force_power_down (struct rtsx_chip*,int) ; 
 int /*<<< orphan*/  rtsx_power_off_card (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_readl (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_set_stat (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_write_cfg_dw (struct rtsx_chip*,int,int,int,int) ; 
 int /*<<< orphan*/  rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_writel (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtsx_enter_ss(struct rtsx_chip *chip)
{
	dev_dbg(rtsx_dev(chip), "Enter Selective Suspend State!\n");

	rtsx_write_register(chip, IRQSTAT0, LINK_RDY_INT, LINK_RDY_INT);

	if (chip->power_down_in_ss) {
		rtsx_power_off_card(chip);
		rtsx_force_power_down(chip, SSC_PDCTL | OC_PDCTL);
	}

	if (CHK_SDIO_EXIST(chip))
		rtsx_write_cfg_dw(chip, CHECK_PID(chip, 0x5288) ? 2 : 1,
				  0xC0, 0xFF00, 0x0100);

	if (chip->auto_delink_en) {
		rtsx_write_register(chip, HOST_SLEEP_STATE, 0x01, 0x01);
	} else {
		if (!chip->phy_debug_mode) {
			u32 tmp;

			tmp = rtsx_readl(chip, RTSX_BIER);
			tmp |= CARD_INT;
			rtsx_writel(chip, RTSX_BIER, tmp);
		}

		rtsx_write_register(chip, CHANGE_LINK_STATE, 0x02, 0);
	}

	rtsx_enter_L1(chip);

	RTSX_CLR_DELINK(chip);
	rtsx_set_stat(chip, RTSX_STAT_SS);
}