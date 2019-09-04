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
struct iwl_mvm {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void iwl_mvm_read_d3_sram(struct iwl_mvm *mvm)
{
#ifdef CONFIG_IWLWIFI_DEBUGFS
	const struct fw_img *img = &mvm->fw->img[IWL_UCODE_WOWLAN];
	u32 len = img->sec[IWL_UCODE_SECTION_DATA].len;
	u32 offs = img->sec[IWL_UCODE_SECTION_DATA].offset;

	if (!mvm->store_d3_resume_sram)
		return;

	if (!mvm->d3_resume_sram) {
		mvm->d3_resume_sram = kzalloc(len, GFP_KERNEL);
		if (!mvm->d3_resume_sram)
			return;
	}

	iwl_trans_read_mem_bytes(mvm->trans, offs, mvm->d3_resume_sram, len);
#endif
}