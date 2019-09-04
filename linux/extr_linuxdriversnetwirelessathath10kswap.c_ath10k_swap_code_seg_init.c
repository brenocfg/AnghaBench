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
struct ath10k_swap_code_seg_info {int dummy; } ;
struct ath10k_fw_file {void* codeswap_data; size_t codeswap_len; struct ath10k_swap_code_seg_info* firmware_swap_code_seg_info; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*) ; 
 struct ath10k_swap_code_seg_info* ath10k_swap_code_seg_alloc (struct ath10k*,size_t) ; 
 int ath10k_swap_code_seg_fill (struct ath10k*,struct ath10k_swap_code_seg_info*,void const*,size_t) ; 
 int /*<<< orphan*/  ath10k_swap_code_seg_free (struct ath10k*,struct ath10k_swap_code_seg_info*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 

int ath10k_swap_code_seg_init(struct ath10k *ar, struct ath10k_fw_file *fw_file)
{
	int ret;
	struct ath10k_swap_code_seg_info *seg_info;
	const void *codeswap_data;
	size_t codeswap_len;

	codeswap_data = fw_file->codeswap_data;
	codeswap_len = fw_file->codeswap_len;

	if (!codeswap_len || !codeswap_data)
		return 0;

	seg_info = ath10k_swap_code_seg_alloc(ar, codeswap_len);
	if (!seg_info) {
		ath10k_err(ar, "failed to allocate fw code swap segment\n");
		return -ENOMEM;
	}

	ret = ath10k_swap_code_seg_fill(ar, seg_info,
					codeswap_data, codeswap_len);

	if (ret) {
		ath10k_warn(ar, "failed to initialize fw code swap segment: %d\n",
			    ret);
		ath10k_swap_code_seg_free(ar, seg_info);
		return ret;
	}

	fw_file->firmware_swap_code_seg_info = seg_info;

	return 0;
}