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
struct TYPE_2__ {int /*<<< orphan*/  dataset_patch_addr; } ;
struct ath6kl {int /*<<< orphan*/  fw_patch_len; int /*<<< orphan*/ * fw_patch; TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_BOOT ; 
 int ath6kl_bmi_write (struct ath6kl*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_bmi_write_hi32 (struct ath6kl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_err (char*,int) ; 
 int /*<<< orphan*/  hi_dset_list_head ; 

__attribute__((used)) static int ath6kl_upload_patch(struct ath6kl *ar)
{
	u32 address;
	int ret;

	if (ar->fw_patch == NULL)
		return 0;

	address = ar->hw.dataset_patch_addr;

	ath6kl_dbg(ATH6KL_DBG_BOOT, "writing patch to 0x%x (%zd B)\n",
		   address, ar->fw_patch_len);

	ret = ath6kl_bmi_write(ar, address, ar->fw_patch, ar->fw_patch_len);
	if (ret) {
		ath6kl_err("Failed to write patch file: %d\n", ret);
		return ret;
	}

	ath6kl_bmi_write_hi32(ar, hi_dset_list_head, address);

	return 0;
}