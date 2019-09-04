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
struct iwl_trans_txq_scd_cfg {int fifo; int sta_id; int aggregate; int /*<<< orphan*/  frame_limit; int /*<<< orphan*/  tid; } ;
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_FRAME_LIMIT ; 
 int /*<<< orphan*/  IWL_MAX_TID_COUNT ; 
 int /*<<< orphan*/  iwl_trans_txq_enable_cfg (struct iwl_trans*,int,int /*<<< orphan*/ ,struct iwl_trans_txq_scd_cfg*,unsigned int) ; 

__attribute__((used)) static inline
void iwl_trans_ac_txq_enable(struct iwl_trans *trans, int queue, int fifo,
			     unsigned int queue_wdg_timeout)
{
	struct iwl_trans_txq_scd_cfg cfg = {
		.fifo = fifo,
		.sta_id = -1,
		.tid = IWL_MAX_TID_COUNT,
		.frame_limit = IWL_FRAME_LIMIT,
		.aggregate = false,
	};

	iwl_trans_txq_enable_cfg(trans, queue, 0, &cfg, queue_wdg_timeout);
}