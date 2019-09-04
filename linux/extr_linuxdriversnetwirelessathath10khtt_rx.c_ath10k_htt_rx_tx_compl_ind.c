#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; } ;
struct htt_tx_done {void* status; int /*<<< orphan*/  msdu_id; } ;
struct TYPE_2__ {int num_msdus; int /*<<< orphan*/ * msdus; int /*<<< orphan*/  flags; } ;
struct htt_resp {TYPE_1__ data_tx_completion; } ;
struct ath10k_htt {int /*<<< orphan*/  txdone_fifo; } ;
struct ath10k {struct ath10k_htt htt; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_HTT ; 
 int /*<<< orphan*/  HTT_DATA_TX_STATUS ; 
#define  HTT_DATA_TX_STATUS_DISCARD 132 
#define  HTT_DATA_TX_STATUS_DOWNLOAD_FAIL 131 
#define  HTT_DATA_TX_STATUS_NO_ACK 130 
#define  HTT_DATA_TX_STATUS_OK 129 
#define  HTT_DATA_TX_STATUS_POSTPONE 128 
 void* HTT_TX_COMPL_STATE_ACK ; 
 void* HTT_TX_COMPL_STATE_DISCARD ; 
 void* HTT_TX_COMPL_STATE_NOACK ; 
 int MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ath10k_txrx_tx_unref (struct ath10k_htt*,struct htt_tx_done*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int,...) ; 
 int /*<<< orphan*/  kfifo_put (int /*<<< orphan*/ *,struct htt_tx_done) ; 

__attribute__((used)) static void ath10k_htt_rx_tx_compl_ind(struct ath10k *ar,
				       struct sk_buff *skb)
{
	struct ath10k_htt *htt = &ar->htt;
	struct htt_resp *resp = (struct htt_resp *)skb->data;
	struct htt_tx_done tx_done = {};
	int status = MS(resp->data_tx_completion.flags, HTT_DATA_TX_STATUS);
	__le16 msdu_id;
	int i;

	switch (status) {
	case HTT_DATA_TX_STATUS_NO_ACK:
		tx_done.status = HTT_TX_COMPL_STATE_NOACK;
		break;
	case HTT_DATA_TX_STATUS_OK:
		tx_done.status = HTT_TX_COMPL_STATE_ACK;
		break;
	case HTT_DATA_TX_STATUS_DISCARD:
	case HTT_DATA_TX_STATUS_POSTPONE:
	case HTT_DATA_TX_STATUS_DOWNLOAD_FAIL:
		tx_done.status = HTT_TX_COMPL_STATE_DISCARD;
		break;
	default:
		ath10k_warn(ar, "unhandled tx completion status %d\n", status);
		tx_done.status = HTT_TX_COMPL_STATE_DISCARD;
		break;
	}

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt tx completion num_msdus %d\n",
		   resp->data_tx_completion.num_msdus);

	for (i = 0; i < resp->data_tx_completion.num_msdus; i++) {
		msdu_id = resp->data_tx_completion.msdus[i];
		tx_done.msdu_id = __le16_to_cpu(msdu_id);

		/* kfifo_put: In practice firmware shouldn't fire off per-CE
		 * interrupt and main interrupt (MSI/-X range case) for the same
		 * HTC service so it should be safe to use kfifo_put w/o lock.
		 *
		 * From kfifo_put() documentation:
		 *  Note that with only one concurrent reader and one concurrent
		 *  writer, you don't need extra locking to use these macro.
		 */
		if (!kfifo_put(&htt->txdone_fifo, tx_done)) {
			ath10k_warn(ar, "txdone fifo overrun, msdu_id %d status %d\n",
				    tx_done.msdu_id, tx_done.status);
			ath10k_txrx_tx_unref(htt, &tx_done);
		}
	}
}