#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ firmware_len; int /*<<< orphan*/ * firmware_data; int /*<<< orphan*/ * firmware; scalar_t__ otp_len; int /*<<< orphan*/ * otp_data; } ;
struct TYPE_3__ {TYPE_2__ fw_file; } ;
struct ath10k {int /*<<< orphan*/ * pre_cal_file; int /*<<< orphan*/ * cal_file; TYPE_1__ normal_mode_fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath10k_swap_code_seg_release (struct ath10k*,TYPE_2__*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_core_free_firmware_files(struct ath10k *ar)
{
	if (!IS_ERR(ar->normal_mode_fw.fw_file.firmware))
		release_firmware(ar->normal_mode_fw.fw_file.firmware);

	if (!IS_ERR(ar->cal_file))
		release_firmware(ar->cal_file);

	if (!IS_ERR(ar->pre_cal_file))
		release_firmware(ar->pre_cal_file);

	ath10k_swap_code_seg_release(ar, &ar->normal_mode_fw.fw_file);

	ar->normal_mode_fw.fw_file.otp_data = NULL;
	ar->normal_mode_fw.fw_file.otp_len = 0;

	ar->normal_mode_fw.fw_file.firmware = NULL;
	ar->normal_mode_fw.fw_file.firmware_data = NULL;
	ar->normal_mode_fw.fw_file.firmware_len = 0;

	ar->cal_file = NULL;
	ar->pre_cal_file = NULL;
}