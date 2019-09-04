#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; } ;
struct mwl8k_vif {scalar_t__ is_hw_crypto_enabled; } ;
struct mwl8k_rx_queue {size_t head; scalar_t__ rxd_count; TYPE_2__* buf; void* rxd; } ;
struct mwl8k_priv {int /*<<< orphan*/  vif_list; int /*<<< orphan*/  pdev; int /*<<< orphan*/  noise; TYPE_1__* rxd_ops; struct mwl8k_rx_queue* rxq; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/  addr1; } ;
struct mwl8k_dma_data {int /*<<< orphan*/  data; struct ieee80211_hdr wh; } ;
struct ieee80211_rx_status {int flag; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;
typedef  int /*<<< orphan*/  status ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_5__ {struct sk_buff* skb; } ;
struct TYPE_4__ {int rxd_size; int (* rxd_process ) (void*,struct ieee80211_rx_status*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 size_t MWL8K_RX_DESCS ; 
 int /*<<< orphan*/  MWL8K_RX_MAXSZ ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int RX_FLAG_DECRYPTED ; 
 int RX_FLAG_IV_STRIPPED ; 
 int RX_FLAG_MMIC_ERROR ; 
 int RX_FLAG_MMIC_STRIPPED ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/  dma_unmap_addr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_has_protected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_auth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_rx_irqsafe (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ieee80211_rx_status*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mwl8k_capture_bssid (struct mwl8k_priv*,void*) ; 
 struct mwl8k_vif* mwl8k_find_vif_bss (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl8k_remove_dma_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl8k_save_beacon (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int stub1 (void*,struct ieee80211_rx_status*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rxq_process(struct ieee80211_hw *hw, int index, int limit)
{
	struct mwl8k_priv *priv = hw->priv;
	struct mwl8k_vif *mwl8k_vif = NULL;
	struct mwl8k_rx_queue *rxq = priv->rxq + index;
	int processed;

	processed = 0;
	while (rxq->rxd_count && limit--) {
		struct sk_buff *skb;
		void *rxd;
		int pkt_len;
		struct ieee80211_rx_status status;
		struct ieee80211_hdr *wh;
		__le16 qos;

		skb = rxq->buf[rxq->head].skb;
		if (skb == NULL)
			break;

		rxd = rxq->rxd + (rxq->head * priv->rxd_ops->rxd_size);

		pkt_len = priv->rxd_ops->rxd_process(rxd, &status, &qos,
							&priv->noise);
		if (pkt_len < 0)
			break;

		rxq->buf[rxq->head].skb = NULL;

		pci_unmap_single(priv->pdev,
				 dma_unmap_addr(&rxq->buf[rxq->head], dma),
				 MWL8K_RX_MAXSZ, PCI_DMA_FROMDEVICE);
		dma_unmap_addr_set(&rxq->buf[rxq->head], dma, 0);

		rxq->head++;
		if (rxq->head == MWL8K_RX_DESCS)
			rxq->head = 0;

		rxq->rxd_count--;

		wh = &((struct mwl8k_dma_data *)skb->data)->wh;

		/*
		 * Check for a pending join operation.  Save a
		 * copy of the beacon and schedule a tasklet to
		 * send a FINALIZE_JOIN command to the firmware.
		 */
		if (mwl8k_capture_bssid(priv, (void *)skb->data))
			mwl8k_save_beacon(hw, skb);

		if (ieee80211_has_protected(wh->frame_control)) {

			/* Check if hw crypto has been enabled for
			 * this bss. If yes, set the status flags
			 * accordingly
			 */
			mwl8k_vif = mwl8k_find_vif_bss(&priv->vif_list,
								wh->addr1);

			if (mwl8k_vif != NULL &&
			    mwl8k_vif->is_hw_crypto_enabled) {
				/*
				 * When MMIC ERROR is encountered
				 * by the firmware, payload is
				 * dropped and only 32 bytes of
				 * mwl8k Firmware header is sent
				 * to the host.
				 *
				 * We need to add four bytes of
				 * key information.  In it
				 * MAC80211 expects keyidx set to
				 * 0 for triggering Counter
				 * Measure of MMIC failure.
				 */
				if (status.flag & RX_FLAG_MMIC_ERROR) {
					struct mwl8k_dma_data *tr;
					tr = (struct mwl8k_dma_data *)skb->data;
					memset((void *)&(tr->data), 0, 4);
					pkt_len += 4;
				}

				if (!ieee80211_is_auth(wh->frame_control))
					status.flag |= RX_FLAG_IV_STRIPPED |
						       RX_FLAG_DECRYPTED |
						       RX_FLAG_MMIC_STRIPPED;
			}
		}

		skb_put(skb, pkt_len);
		mwl8k_remove_dma_header(skb, qos);
		memcpy(IEEE80211_SKB_RXCB(skb), &status, sizeof(status));
		ieee80211_rx_irqsafe(hw, skb);

		processed++;
	}

	return processed;
}