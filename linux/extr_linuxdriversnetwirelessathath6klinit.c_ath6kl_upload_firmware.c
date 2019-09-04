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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  app_start_override_addr; int /*<<< orphan*/  app_load_addr; } ;
struct ath6kl {scalar_t__ target_type; TYPE_1__ hw; int /*<<< orphan*/  fw_len; int /*<<< orphan*/ * fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_BOOT ; 
 scalar_t__ TARGET_TYPE_AR6004 ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int ath6kl_bmi_fast_download (struct ath6kl*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_bmi_set_app_start (struct ath6kl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_err (char*,int) ; 

__attribute__((used)) static int ath6kl_upload_firmware(struct ath6kl *ar)
{
	u32 address;
	int ret;

	if (WARN_ON(ar->fw == NULL))
		return 0;

	address = ar->hw.app_load_addr;

	ath6kl_dbg(ATH6KL_DBG_BOOT, "writing firmware to 0x%x (%zd B)\n",
		   address, ar->fw_len);

	ret = ath6kl_bmi_fast_download(ar, address, ar->fw, ar->fw_len);

	if (ret) {
		ath6kl_err("Failed to write firmware: %d\n", ret);
		return ret;
	}

	/*
	 * Set starting address for firmware
	 * Don't need to setup app_start override addr on AR6004
	 */
	if (ar->target_type != TARGET_TYPE_AR6004) {
		address = ar->hw.app_start_override_addr;
		ath6kl_bmi_set_app_start(ar, address);
	}
	return ret;
}