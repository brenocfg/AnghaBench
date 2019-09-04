#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* board; int /*<<< orphan*/  board_len; int /*<<< orphan*/  board_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  board; int /*<<< orphan*/  dir; } ;
struct TYPE_9__ {TYPE_2__ fw; } ;
struct ath10k {TYPE_1__ normal_mode_fw; TYPE_3__ hw_params; } ;
struct TYPE_10__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (TYPE_4__*) ; 
 int PTR_ERR (TYPE_4__*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*) ; 
 TYPE_4__* ath10k_fetch_fw_file (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_core_fetch_board_data_api_1(struct ath10k *ar)
{
	if (!ar->hw_params.fw.board) {
		ath10k_err(ar, "failed to find board file fw entry\n");
		return -EINVAL;
	}

	ar->normal_mode_fw.board = ath10k_fetch_fw_file(ar,
							ar->hw_params.fw.dir,
							ar->hw_params.fw.board);
	if (IS_ERR(ar->normal_mode_fw.board))
		return PTR_ERR(ar->normal_mode_fw.board);

	ar->normal_mode_fw.board_data = ar->normal_mode_fw.board->data;
	ar->normal_mode_fw.board_len = ar->normal_mode_fw.board->size;

	return 0;
}