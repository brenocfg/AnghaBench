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
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct ieee80211_hw {struct adm8211_priv* priv; } ;
struct adm8211_priv {unsigned int cur_tx; int dirty_tx; int tx_ring_size; int /*<<< orphan*/  lock; TYPE_2__* tx_ring; TYPE_1__* tx_buffers; int /*<<< orphan*/  pdev; } ;
typedef  int dma_addr_t ;
struct TYPE_4__ {void* status; void* length; void* buffer1; } ;
struct TYPE_3__ {int mapping; size_t hdrlen; struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM8211_CSR_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int TDES0_CONTROL_OWN ; 
 int TDES1_CONTROL_FS ; 
 int TDES1_CONTROL_IC ; 
 int TDES1_CONTROL_LS ; 
 int TDES1_CONTROL_TER ; 
 int /*<<< orphan*/  TDR ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ieee80211_stop_queue (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int) ; 
 int pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int adm8211_tx_raw(struct ieee80211_hw *dev, struct sk_buff *skb,
			   u16 plcp_signal,
			   size_t hdrlen)
{
	struct adm8211_priv *priv = dev->priv;
	unsigned long flags;
	dma_addr_t mapping;
	unsigned int entry;
	u32 flag;

	mapping = pci_map_single(priv->pdev, skb->data, skb->len,
				 PCI_DMA_TODEVICE);
	if (pci_dma_mapping_error(priv->pdev, mapping))
		return -ENOMEM;

	spin_lock_irqsave(&priv->lock, flags);

	if (priv->cur_tx - priv->dirty_tx == priv->tx_ring_size / 2)
		flag = TDES1_CONTROL_IC | TDES1_CONTROL_LS | TDES1_CONTROL_FS;
	else
		flag = TDES1_CONTROL_LS | TDES1_CONTROL_FS;

	if (priv->cur_tx - priv->dirty_tx == priv->tx_ring_size - 2)
		ieee80211_stop_queue(dev, 0);

	entry = priv->cur_tx % priv->tx_ring_size;

	priv->tx_buffers[entry].skb = skb;
	priv->tx_buffers[entry].mapping = mapping;
	priv->tx_buffers[entry].hdrlen = hdrlen;
	priv->tx_ring[entry].buffer1 = cpu_to_le32(mapping);

	if (entry == priv->tx_ring_size - 1)
		flag |= TDES1_CONTROL_TER;
	priv->tx_ring[entry].length = cpu_to_le32(flag | skb->len);

	/* Set TX rate (SIGNAL field in PLCP PPDU format) */
	flag = TDES0_CONTROL_OWN | (plcp_signal << 20) | 8 /* ? */;
	priv->tx_ring[entry].status = cpu_to_le32(flag);

	priv->cur_tx++;

	spin_unlock_irqrestore(&priv->lock, flags);

	/* Trigger transmit poll */
	ADM8211_CSR_WRITE(TDR, 0);

	return 0;
}