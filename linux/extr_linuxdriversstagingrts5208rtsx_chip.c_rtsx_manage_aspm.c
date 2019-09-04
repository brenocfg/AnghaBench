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
typedef  int /*<<< orphan*/  u8 ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_PID (struct rtsx_chip*,int) ; 
 int /*<<< orphan*/  rtsx_monitor_aspm_config (struct rtsx_chip*) ; 

__attribute__((used)) static void rtsx_manage_aspm(struct rtsx_chip *chip)
{
	u8 data;

	if (!CHECK_PID(chip, 0x5208))
		return;

	rtsx_monitor_aspm_config(chip);

#ifdef SUPPORT_SDIO_ASPM
	if (!CHK_SDIO_EXIST(chip) || CHK_SDIO_IGNORED(chip) ||
	    !chip->aspm_l0s_l1_en || !chip->dynamic_aspm)
		return;

	if (chip->sd_io) {
		dynamic_configure_sdio_aspm(chip);
		return;
	}

	if (chip->sdio_aspm)
		return;

	dev_dbg(rtsx_dev(chip), "SDIO enter ASPM!\n");
	data = 0x30 | (chip->aspm_level[1] << 2);
	rtsx_write_register(chip, ASPM_FORCE_CTL, 0xFC, data);
	chip->sdio_aspm = 1;
#endif
}