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
struct wil_net_stats {int /*<<< orphan*/  rx_csum_err; int /*<<< orphan*/  rx_amsdu_error; int /*<<< orphan*/  rx_replay; int /*<<< orphan*/  rx_key_error; int /*<<< orphan*/  rx_mic_error; } ;
struct wil6210_priv {int dummy; } ;
struct sk_buff {void* ip_summed; } ;

/* Variables and functions */
 void* CHECKSUM_UNNECESSARY ; 
 int EFAULT ; 
 int WIL_RX_EDMA_ERROR_AMSDU ; 
 int WIL_RX_EDMA_ERROR_KEY ; 
 int WIL_RX_EDMA_ERROR_MIC ; 
 int WIL_RX_EDMA_ERROR_REPLAY ; 
 int /*<<< orphan*/  wil_dbg_txrx (struct wil6210_priv*,char*,...) ; 
 int wil_rx_status_get_error (void*) ; 
 int wil_rx_status_get_l2_rx_status (void*) ; 
 int wil_rx_status_get_l3_rx_status (void*) ; 
 int wil_rx_status_get_l4_rx_status (void*) ; 
 void* wil_skb_rxstatus (struct sk_buff*) ; 

__attribute__((used)) static int wil_rx_error_check_edma(struct wil6210_priv *wil,
				   struct sk_buff *skb,
				   struct wil_net_stats *stats)
{
	int error;
	int l2_rx_status;
	int l3_rx_status;
	int l4_rx_status;
	void *msg = wil_skb_rxstatus(skb);

	error = wil_rx_status_get_error(msg);
	if (!error) {
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		return 0;
	}

	l2_rx_status = wil_rx_status_get_l2_rx_status(msg);
	if (l2_rx_status != 0) {
		wil_dbg_txrx(wil, "L2 RX error, l2_rx_status=0x%x\n",
			     l2_rx_status);
		/* Due to HW issue, KEY error will trigger a MIC error */
		if (l2_rx_status & WIL_RX_EDMA_ERROR_MIC) {
			wil_dbg_txrx(wil,
				     "L2 MIC/KEY error, dropping packet\n");
			stats->rx_mic_error++;
		}
		if (l2_rx_status & WIL_RX_EDMA_ERROR_KEY) {
			wil_dbg_txrx(wil, "L2 KEY error, dropping packet\n");
			stats->rx_key_error++;
		}
		if (l2_rx_status & WIL_RX_EDMA_ERROR_REPLAY) {
			wil_dbg_txrx(wil,
				     "L2 REPLAY error, dropping packet\n");
			stats->rx_replay++;
		}
		if (l2_rx_status & WIL_RX_EDMA_ERROR_AMSDU) {
			wil_dbg_txrx(wil,
				     "L2 AMSDU error, dropping packet\n");
			stats->rx_amsdu_error++;
		}
		return -EFAULT;
	}

	l3_rx_status = wil_rx_status_get_l3_rx_status(msg);
	l4_rx_status = wil_rx_status_get_l4_rx_status(msg);
	if (!l3_rx_status && !l4_rx_status)
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	/* If HW reports bad checksum, let IP stack re-check it
	 * For example, HW don't understand Microsoft IP stack that
	 * mis-calculates TCP checksum - if it should be 0x0,
	 * it writes 0xffff in violation of RFC 1624
	 */
	else
		stats->rx_csum_err++;

	return 0;
}