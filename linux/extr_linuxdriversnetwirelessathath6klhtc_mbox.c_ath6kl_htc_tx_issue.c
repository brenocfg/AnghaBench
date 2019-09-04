#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct htc_target {TYPE_4__* dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  seqno; } ;
struct TYPE_8__ {TYPE_1__ tx; } ;
struct htc_packet {int status; int /*<<< orphan*/  buf; int /*<<< orphan*/  endpoint; TYPE_2__ info; scalar_t__ act_len; int /*<<< orphan*/  completion; } ;
struct TYPE_9__ {int /*<<< orphan*/  htc_addr; } ;
struct TYPE_11__ {TYPE_3__ mbox_info; } ;
struct TYPE_10__ {TYPE_5__* ar; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_HTC ; 
 scalar_t__ CALC_TXRX_PADDED_LEN (struct htc_target*,scalar_t__) ; 
 int /*<<< orphan*/  HIF_WR_ASYNC_BLOCK_INC ; 
 int /*<<< orphan*/  HIF_WR_SYNC_BLOCK_INC ; 
 scalar_t__ HTC_HDR_LENGTH ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int hif_read_write_sync (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int hif_write_async (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct htc_packet*) ; 
 int /*<<< orphan*/  trace_ath6kl_htc_tx (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ath6kl_htc_tx_issue(struct htc_target *target,
			       struct htc_packet *packet)
{
	int status;
	bool sync = false;
	u32 padded_len, send_len;

	if (!packet->completion)
		sync = true;

	send_len = packet->act_len + HTC_HDR_LENGTH;

	padded_len = CALC_TXRX_PADDED_LEN(target, send_len);

	ath6kl_dbg(ATH6KL_DBG_HTC,
		   "htc tx issue len %d seqno %d padded_len %d mbox 0x%X %s\n",
		   send_len, packet->info.tx.seqno, padded_len,
		   target->dev->ar->mbox_info.htc_addr,
		   sync ? "sync" : "async");

	if (sync) {
		status = hif_read_write_sync(target->dev->ar,
				target->dev->ar->mbox_info.htc_addr,
				 packet->buf, padded_len,
				 HIF_WR_SYNC_BLOCK_INC);

		packet->status = status;
		packet->buf += HTC_HDR_LENGTH;
	} else
		status = hif_write_async(target->dev->ar,
				target->dev->ar->mbox_info.htc_addr,
				packet->buf, padded_len,
				HIF_WR_ASYNC_BLOCK_INC, packet);

	trace_ath6kl_htc_tx(status, packet->endpoint, packet->buf, send_len);

	return status;
}