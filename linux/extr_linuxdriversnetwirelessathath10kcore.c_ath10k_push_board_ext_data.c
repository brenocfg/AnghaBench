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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ board_size; scalar_t__ board_ext_size; } ;
struct TYPE_3__ {TYPE_2__ fw; } ;
struct ath10k {TYPE_1__ hw_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int EINVAL ; 
 int ath10k_bmi_read32 (struct ath10k*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int ath10k_bmi_write32 (struct ath10k*,int /*<<< orphan*/ ,scalar_t__) ; 
 int ath10k_bmi_write_memory (struct ath10k*,scalar_t__,void const*,scalar_t__) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int,...) ; 
 int /*<<< orphan*/  hi_board_ext_data ; 
 int /*<<< orphan*/  hi_board_ext_data_config ; 

__attribute__((used)) static int ath10k_push_board_ext_data(struct ath10k *ar, const void *data,
				      size_t data_len)
{
	u32 board_data_size = ar->hw_params.fw.board_size;
	u32 board_ext_data_size = ar->hw_params.fw.board_ext_size;
	u32 board_ext_data_addr;
	int ret;

	ret = ath10k_bmi_read32(ar, hi_board_ext_data, &board_ext_data_addr);
	if (ret) {
		ath10k_err(ar, "could not read board ext data addr (%d)\n",
			   ret);
		return ret;
	}

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "boot push board extended data addr 0x%x\n",
		   board_ext_data_addr);

	if (board_ext_data_addr == 0)
		return 0;

	if (data_len != (board_data_size + board_ext_data_size)) {
		ath10k_err(ar, "invalid board (ext) data sizes %zu != %d+%d\n",
			   data_len, board_data_size, board_ext_data_size);
		return -EINVAL;
	}

	ret = ath10k_bmi_write_memory(ar, board_ext_data_addr,
				      data + board_data_size,
				      board_ext_data_size);
	if (ret) {
		ath10k_err(ar, "could not write board ext data (%d)\n", ret);
		return ret;
	}

	ret = ath10k_bmi_write32(ar, hi_board_ext_data_config,
				 (board_ext_data_size << 16) | 1);
	if (ret) {
		ath10k_err(ar, "could not write board ext data bit (%d)\n",
			   ret);
		return ret;
	}

	return 0;
}