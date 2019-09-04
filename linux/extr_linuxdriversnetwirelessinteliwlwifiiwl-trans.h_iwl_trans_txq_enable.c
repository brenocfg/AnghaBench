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
typedef  int /*<<< orphan*/  u16 ;
struct iwl_trans_txq_scd_cfg {int fifo; int sta_id; int tid; int frame_limit; int aggregate; } ;
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_trans_txq_enable_cfg (struct iwl_trans*,int,int /*<<< orphan*/ ,struct iwl_trans_txq_scd_cfg*,unsigned int) ; 

__attribute__((used)) static inline void iwl_trans_txq_enable(struct iwl_trans *trans, int queue,
					int fifo, int sta_id, int tid,
					int frame_limit, u16 ssn,
					unsigned int queue_wdg_timeout)
{
	struct iwl_trans_txq_scd_cfg cfg = {
		.fifo = fifo,
		.sta_id = sta_id,
		.tid = tid,
		.frame_limit = frame_limit,
		.aggregate = sta_id >= 0,
	};

	iwl_trans_txq_enable_cfg(trans, queue, ssn, &cfg, queue_wdg_timeout);
}