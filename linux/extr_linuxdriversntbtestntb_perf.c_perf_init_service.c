#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct perf_ctx {scalar_t__ pcnt; TYPE_1__* ntb; int /*<<< orphan*/  cmd_recv; int /*<<< orphan*/  cmd_send; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int GENMASK_ULL (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PERF_MSG_CNT ; 
 scalar_t__ PERF_SPAD_CNT (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ntb_db_valid_mask (TYPE_1__*) ; 
 scalar_t__ ntb_msg_count (TYPE_1__*) ; 
 scalar_t__ ntb_peer_mw_count (TYPE_1__*) ; 
 scalar_t__ ntb_spad_count (TYPE_1__*) ; 
 int /*<<< orphan*/  perf_msg_cmd_recv ; 
 int /*<<< orphan*/  perf_msg_cmd_send ; 
 int /*<<< orphan*/  perf_spad_cmd_recv ; 
 int /*<<< orphan*/  perf_spad_cmd_send ; 

__attribute__((used)) static int perf_init_service(struct perf_ctx *perf)
{
	u64 mask;

	if (ntb_peer_mw_count(perf->ntb) < perf->pcnt + 1) {
		dev_err(&perf->ntb->dev, "Not enough memory windows\n");
		return -EINVAL;
	}

	if (ntb_msg_count(perf->ntb) >= PERF_MSG_CNT) {
		perf->cmd_send = perf_msg_cmd_send;
		perf->cmd_recv = perf_msg_cmd_recv;

		dev_dbg(&perf->ntb->dev, "Message service initialized\n");

		return 0;
	}

	dev_dbg(&perf->ntb->dev, "Message service unsupported\n");

	mask = GENMASK_ULL(perf->pcnt, 0);
	if (ntb_spad_count(perf->ntb) >= PERF_SPAD_CNT(perf->pcnt) &&
	    (ntb_db_valid_mask(perf->ntb) & mask) == mask) {
		perf->cmd_send = perf_spad_cmd_send;
		perf->cmd_recv = perf_spad_cmd_recv;

		dev_dbg(&perf->ntb->dev, "Scratchpad service initialized\n");

		return 0;
	}

	dev_dbg(&perf->ntb->dev, "Scratchpad service unsupported\n");

	dev_err(&perf->ntb->dev, "Command services unsupported\n");

	return -EINVAL;
}