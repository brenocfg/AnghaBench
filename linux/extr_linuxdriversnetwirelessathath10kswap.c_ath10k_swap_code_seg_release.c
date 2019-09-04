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
struct ath10k_fw_file {int /*<<< orphan*/ * firmware_swap_code_seg_info; scalar_t__ codeswap_len; int /*<<< orphan*/ * codeswap_data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_swap_code_seg_free (struct ath10k*,int /*<<< orphan*/ *) ; 

void ath10k_swap_code_seg_release(struct ath10k *ar,
				  struct ath10k_fw_file *fw_file)
{
	ath10k_swap_code_seg_free(ar, fw_file->firmware_swap_code_seg_info);

	/* FIXME: these two assignments look to bein wrong place! Shouldn't
	 * they be in ath10k_core_free_firmware_files() like the rest?
	 */
	fw_file->codeswap_data = NULL;
	fw_file->codeswap_len = 0;

	fw_file->firmware_swap_code_seg_info = NULL;
}