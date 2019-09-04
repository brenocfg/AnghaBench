#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  otp_len; scalar_t__ otp_data; } ;
struct ath10k_fw_components {TYPE_4__ fw_file; int /*<<< orphan*/  board_len; int /*<<< orphan*/  board_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  otp_len; scalar_t__ otp_data; } ;
struct TYPE_8__ {TYPE_2__ fw_file; int /*<<< orphan*/  board_len; int /*<<< orphan*/  board_data; } ;
struct TYPE_6__ {struct ath10k_fw_components utf_mode_fw; } ;
struct ath10k {TYPE_3__ normal_mode_fw; TYPE_1__ testmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_TESTMODE ; 
 int /*<<< orphan*/  ATH10K_FW_UTF_API2_FILE ; 
 int ath10k_core_fetch_firmware_api_n (struct ath10k*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  ath10k_info (struct ath10k*,char*) ; 
 int ath10k_tm_fetch_utf_firmware_api_1 (struct ath10k*,TYPE_4__*) ; 

__attribute__((used)) static int ath10k_tm_fetch_firmware(struct ath10k *ar)
{
	struct ath10k_fw_components *utf_mode_fw;
	int ret;

	ret = ath10k_core_fetch_firmware_api_n(ar, ATH10K_FW_UTF_API2_FILE,
					       &ar->testmode.utf_mode_fw.fw_file);
	if (ret == 0) {
		ath10k_dbg(ar, ATH10K_DBG_TESTMODE, "testmode using fw utf api 2");
		goto out;
	}

	ret = ath10k_tm_fetch_utf_firmware_api_1(ar, &ar->testmode.utf_mode_fw.fw_file);
	if (ret) {
		ath10k_err(ar, "failed to fetch utf firmware binary: %d", ret);
		return ret;
	}

	ath10k_dbg(ar, ATH10K_DBG_TESTMODE, "testmode using utf api 1");

out:
	utf_mode_fw = &ar->testmode.utf_mode_fw;

	/* Use the same board data file as the normal firmware uses (but
	 * it's still "owned" by normal_mode_fw so we shouldn't free it.
	 */
	utf_mode_fw->board_data = ar->normal_mode_fw.board_data;
	utf_mode_fw->board_len = ar->normal_mode_fw.board_len;

	if (!utf_mode_fw->fw_file.otp_data) {
		ath10k_info(ar, "utf.bin didn't contain otp binary, taking it from the normal mode firmware");
		utf_mode_fw->fw_file.otp_data = ar->normal_mode_fw.fw_file.otp_data;
		utf_mode_fw->fw_file.otp_len = ar->normal_mode_fw.fw_file.otp_len;
	}

	return 0;
}