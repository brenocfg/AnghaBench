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
typedef  int u32 ;
struct TYPE_2__ {int flags; } ;
struct ath6kl {scalar_t__ target_type; TYPE_1__ hw; } ;

/* Variables and functions */
 int ATH6KL_ANALOG_PLL_REGISTER ; 
 int /*<<< orphan*/  ATH6KL_DBG_TRC ; 
 int ATH6KL_HW_SDIO_CRC_ERROR_WAR ; 
 int ATH6KL_OPTION_SLEEP_DISABLE ; 
 int CPU_CLOCK_ADDRESS ; 
 int /*<<< orphan*/  CPU_CLOCK_STANDARD ; 
 int EINVAL ; 
 int GPIO_BASE_ADDRESS ; 
 int GPIO_PIN10_ADDRESS ; 
 int GPIO_PIN11_ADDRESS ; 
 int GPIO_PIN12_ADDRESS ; 
 int GPIO_PIN13_ADDRESS ; 
 int GPIO_PIN9_ADDRESS ; 
 int LOCAL_SCRATCH_ADDRESS ; 
 int LPO_CAL_ADDRESS ; 
 int /*<<< orphan*/  LPO_CAL_ENABLE ; 
 int MBOX_BASE_ADDRESS ; 
 int RTC_BASE_ADDRESS ; 
 int SM (int /*<<< orphan*/ ,int) ; 
 int SYSTEM_SLEEP_ADDRESS ; 
 int /*<<< orphan*/  SYSTEM_SLEEP_DISABLE ; 
 scalar_t__ TARGET_TYPE_AR6003 ; 
 scalar_t__ TARGET_TYPE_AR6004 ; 
 int ath6kl_bmi_reg_read (struct ath6kl*,int,int*) ; 
 int ath6kl_bmi_reg_write (struct ath6kl*,int,int) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ath6kl_err (char*) ; 
 int ath6kl_upload_board_file (struct ath6kl*) ; 
 int ath6kl_upload_firmware (struct ath6kl*) ; 
 int ath6kl_upload_otp (struct ath6kl*) ; 
 int ath6kl_upload_patch (struct ath6kl*) ; 
 int ath6kl_upload_testscript (struct ath6kl*) ; 

__attribute__((used)) static int ath6kl_init_upload(struct ath6kl *ar)
{
	u32 param, options, sleep, address;
	int status = 0;

	if (ar->target_type != TARGET_TYPE_AR6003 &&
	    ar->target_type != TARGET_TYPE_AR6004)
		return -EINVAL;

	/* temporarily disable system sleep */
	address = MBOX_BASE_ADDRESS + LOCAL_SCRATCH_ADDRESS;
	status = ath6kl_bmi_reg_read(ar, address, &param);
	if (status)
		return status;

	options = param;

	param |= ATH6KL_OPTION_SLEEP_DISABLE;
	status = ath6kl_bmi_reg_write(ar, address, param);
	if (status)
		return status;

	address = RTC_BASE_ADDRESS + SYSTEM_SLEEP_ADDRESS;
	status = ath6kl_bmi_reg_read(ar, address, &param);
	if (status)
		return status;

	sleep = param;

	param |= SM(SYSTEM_SLEEP_DISABLE, 1);
	status = ath6kl_bmi_reg_write(ar, address, param);
	if (status)
		return status;

	ath6kl_dbg(ATH6KL_DBG_TRC, "old options: %d, old sleep: %d\n",
		   options, sleep);

	/* program analog PLL register */
	/* no need to control 40/44MHz clock on AR6004 */
	if (ar->target_type != TARGET_TYPE_AR6004) {
		status = ath6kl_bmi_reg_write(ar, ATH6KL_ANALOG_PLL_REGISTER,
					      0xF9104001);

		if (status)
			return status;

		/* Run at 80/88MHz by default */
		param = SM(CPU_CLOCK_STANDARD, 1);

		address = RTC_BASE_ADDRESS + CPU_CLOCK_ADDRESS;
		status = ath6kl_bmi_reg_write(ar, address, param);
		if (status)
			return status;
	}

	param = 0;
	address = RTC_BASE_ADDRESS + LPO_CAL_ADDRESS;
	param = SM(LPO_CAL_ENABLE, 1);
	status = ath6kl_bmi_reg_write(ar, address, param);
	if (status)
		return status;

	/* WAR to avoid SDIO CRC err */
	if (ar->hw.flags & ATH6KL_HW_SDIO_CRC_ERROR_WAR) {
		ath6kl_err("temporary war to avoid sdio crc error\n");

		param = 0x28;
		address = GPIO_BASE_ADDRESS + GPIO_PIN9_ADDRESS;
		status = ath6kl_bmi_reg_write(ar, address, param);
		if (status)
			return status;

		param = 0x20;

		address = GPIO_BASE_ADDRESS + GPIO_PIN10_ADDRESS;
		status = ath6kl_bmi_reg_write(ar, address, param);
		if (status)
			return status;

		address = GPIO_BASE_ADDRESS + GPIO_PIN11_ADDRESS;
		status = ath6kl_bmi_reg_write(ar, address, param);
		if (status)
			return status;

		address = GPIO_BASE_ADDRESS + GPIO_PIN12_ADDRESS;
		status = ath6kl_bmi_reg_write(ar, address, param);
		if (status)
			return status;

		address = GPIO_BASE_ADDRESS + GPIO_PIN13_ADDRESS;
		status = ath6kl_bmi_reg_write(ar, address, param);
		if (status)
			return status;
	}

	/* write EEPROM data to Target RAM */
	status = ath6kl_upload_board_file(ar);
	if (status)
		return status;

	/* transfer One time Programmable data */
	status = ath6kl_upload_otp(ar);
	if (status)
		return status;

	/* Download Target firmware */
	status = ath6kl_upload_firmware(ar);
	if (status)
		return status;

	status = ath6kl_upload_patch(ar);
	if (status)
		return status;

	/* Download the test script */
	status = ath6kl_upload_testscript(ar);
	if (status)
		return status;

	/* Restore system sleep */
	address = RTC_BASE_ADDRESS + SYSTEM_SLEEP_ADDRESS;
	status = ath6kl_bmi_reg_write(ar, address, sleep);
	if (status)
		return status;

	address = MBOX_BASE_ADDRESS + LOCAL_SCRATCH_ADDRESS;
	param = options | 0x20;
	status = ath6kl_bmi_reg_write(ar, address, param);
	if (status)
		return status;

	return status;
}