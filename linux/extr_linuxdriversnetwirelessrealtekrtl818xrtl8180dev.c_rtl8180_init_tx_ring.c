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
typedef  scalar_t__ u32 ;
struct rtl8180_tx_desc {int /*<<< orphan*/  next_tx_desc; } ;
struct rtl8180_priv {TYPE_1__* tx_ring; int /*<<< orphan*/  pdev; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct rtl8180_priv* priv; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {unsigned int entries; int /*<<< orphan*/  queue; scalar_t__ idx; scalar_t__ dma; struct rtl8180_tx_desc* desc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 struct rtl8180_tx_desc* pci_zalloc_consistent (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static int rtl8180_init_tx_ring(struct ieee80211_hw *dev,
				unsigned int prio, unsigned int entries)
{
	struct rtl8180_priv *priv = dev->priv;
	struct rtl8180_tx_desc *ring;
	dma_addr_t dma;
	int i;

	ring = pci_zalloc_consistent(priv->pdev, sizeof(*ring) * entries,
				     &dma);
	if (!ring || (unsigned long)ring & 0xFF) {
		wiphy_err(dev->wiphy, "Cannot allocate TX ring (prio = %d)\n",
			  prio);
		return -ENOMEM;
	}

	priv->tx_ring[prio].desc = ring;
	priv->tx_ring[prio].dma = dma;
	priv->tx_ring[prio].idx = 0;
	priv->tx_ring[prio].entries = entries;
	skb_queue_head_init(&priv->tx_ring[prio].queue);

	for (i = 0; i < entries; i++)
		ring[i].next_tx_desc =
			cpu_to_le32((u32)dma + ((i + 1) % entries) * sizeof(*ring));

	return 0;
}