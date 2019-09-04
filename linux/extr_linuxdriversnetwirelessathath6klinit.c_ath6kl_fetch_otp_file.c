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
struct TYPE_4__ {char* otp; char* dir; } ;
struct TYPE_3__ {TYPE_2__ fw; } ;
struct ath6kl {int /*<<< orphan*/  fw_otp_len; int /*<<< orphan*/ * fw_otp; TYPE_1__ hw; } ;
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_BOOT ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath6kl_err (char*,char*,int) ; 
 int ath6kl_get_fw (struct ath6kl*,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static int ath6kl_fetch_otp_file(struct ath6kl *ar)
{
	char filename[100];
	int ret;

	if (ar->fw_otp != NULL)
		return 0;

	if (ar->hw.fw.otp == NULL) {
		ath6kl_dbg(ATH6KL_DBG_BOOT,
			   "no OTP file configured for this hw\n");
		return 0;
	}

	snprintf(filename, sizeof(filename), "%s/%s",
		 ar->hw.fw.dir, ar->hw.fw.otp);

	ret = ath6kl_get_fw(ar, filename, &ar->fw_otp,
			    &ar->fw_otp_len);
	if (ret) {
		ath6kl_err("Failed to get OTP file %s: %d\n",
			   filename, ret);
		return ret;
	}

	return 0;
}