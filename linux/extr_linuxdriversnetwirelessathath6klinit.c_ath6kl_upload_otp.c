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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ app_start_override_addr; scalar_t__ app_load_addr; } ;
struct ath6kl {TYPE_1__ hw; int /*<<< orphan*/  fw_otp_len; int /*<<< orphan*/ * fw_otp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_BOOT ; 
 int /*<<< orphan*/  ath6kl_bmi_execute (struct ath6kl*,scalar_t__,scalar_t__*) ; 
 int ath6kl_bmi_fast_download (struct ath6kl*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ath6kl_bmi_read_hi32 (struct ath6kl*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  ath6kl_err (char*,int) ; 
 int /*<<< orphan*/  hi_app_start ; 

__attribute__((used)) static int ath6kl_upload_otp(struct ath6kl *ar)
{
	u32 address, param;
	bool from_hw = false;
	int ret;

	if (ar->fw_otp == NULL)
		return 0;

	address = ar->hw.app_load_addr;

	ath6kl_dbg(ATH6KL_DBG_BOOT, "writing otp to 0x%x (%zd B)\n", address,
		   ar->fw_otp_len);

	ret = ath6kl_bmi_fast_download(ar, address, ar->fw_otp,
				       ar->fw_otp_len);
	if (ret) {
		ath6kl_err("Failed to upload OTP file: %d\n", ret);
		return ret;
	}

	/* read firmware start address */
	ret = ath6kl_bmi_read_hi32(ar, hi_app_start, &address);

	if (ret) {
		ath6kl_err("Failed to read hi_app_start: %d\n", ret);
		return ret;
	}

	if (ar->hw.app_start_override_addr == 0) {
		ar->hw.app_start_override_addr = address;
		from_hw = true;
	}

	ath6kl_dbg(ATH6KL_DBG_BOOT, "app_start_override_addr%s 0x%x\n",
		   from_hw ? " (from hw)" : "",
		   ar->hw.app_start_override_addr);

	/* execute the OTP code */
	ath6kl_dbg(ATH6KL_DBG_BOOT, "executing OTP at 0x%x\n",
		   ar->hw.app_start_override_addr);
	param = 0;
	ath6kl_bmi_execute(ar, ar->hw.app_start_override_addr, &param);

	return ret;
}