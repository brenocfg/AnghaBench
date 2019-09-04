#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct perf_ctx {scalar_t__ cmd_send; TYPE_1__* ntb; int /*<<< orphan*/  gidx; } ;
struct TYPE_14__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT_ULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTB_SPEED_AUTO ; 
 int /*<<< orphan*/  NTB_WIDTH_AUTO ; 
 int /*<<< orphan*/  PERF_CMD_INVAL ; 
 int PERF_SPAD_NOTIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ffs64 (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ntb_clear_ctx (TYPE_1__*) ; 
 int ntb_db_clear_mask (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ntb_db_set_mask (TYPE_1__*,int) ; 
 int ntb_db_valid_mask (TYPE_1__*) ; 
 int /*<<< orphan*/  ntb_link_enable (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_link_event (TYPE_1__*) ; 
 int ntb_msg_clear_mask (TYPE_1__*,int) ; 
 int ntb_msg_inbits (TYPE_1__*) ; 
 int ntb_msg_outbits (TYPE_1__*) ; 
 int /*<<< orphan*/  ntb_msg_set_mask (TYPE_1__*,int) ; 
 int ntb_set_ctx (TYPE_1__*,struct perf_ctx*,int /*<<< orphan*/ *) ; 
 int ntb_spad_count (TYPE_1__*) ; 
 int /*<<< orphan*/  ntb_spad_write (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ perf_msg_cmd_send ; 
 int /*<<< orphan*/  perf_ops ; 

__attribute__((used)) static int perf_enable_service(struct perf_ctx *perf)
{
	u64 mask, incmd_bit;
	int ret, sidx, scnt;

	mask = ntb_db_valid_mask(perf->ntb);
	(void)ntb_db_set_mask(perf->ntb, mask);

	ret = ntb_set_ctx(perf->ntb, perf, &perf_ops);
	if (ret)
		return ret;

	if (perf->cmd_send == perf_msg_cmd_send) {
		u64 inbits, outbits;

		inbits = ntb_msg_inbits(perf->ntb);
		outbits = ntb_msg_outbits(perf->ntb);
		(void)ntb_msg_set_mask(perf->ntb, inbits | outbits);

		incmd_bit = BIT_ULL(__ffs64(inbits));
		ret = ntb_msg_clear_mask(perf->ntb, incmd_bit);

		dev_dbg(&perf->ntb->dev, "MSG sts unmasked %#llx\n", incmd_bit);
	} else {
		scnt = ntb_spad_count(perf->ntb);
		for (sidx = 0; sidx < scnt; sidx++)
			ntb_spad_write(perf->ntb, sidx, PERF_CMD_INVAL);
		incmd_bit = PERF_SPAD_NOTIFY(perf->gidx);
		ret = ntb_db_clear_mask(perf->ntb, incmd_bit);

		dev_dbg(&perf->ntb->dev, "DB bits unmasked %#llx\n", incmd_bit);
	}
	if (ret) {
		ntb_clear_ctx(perf->ntb);
		return ret;
	}

	ntb_link_enable(perf->ntb, NTB_SPEED_AUTO, NTB_WIDTH_AUTO);
	/* Might be not necessary */
	ntb_link_event(perf->ntb);

	return 0;
}