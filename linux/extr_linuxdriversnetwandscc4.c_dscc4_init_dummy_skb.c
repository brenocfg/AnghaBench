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
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct dscc4_dev_priv {int tx_dirty; struct sk_buff** tx_skbuff; struct TxFD* tx_fd; TYPE_2__* pci_priv; } ;
struct device {int dummy; } ;
struct TxFD {int state; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int DUMMY_SKB_SIZE ; 
 int FrameEnd ; 
 int TO_STATE_TX (int) ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  version ; 

__attribute__((used)) static struct sk_buff *dscc4_init_dummy_skb(struct dscc4_dev_priv *dpriv)
{
	struct sk_buff *skb;

	skb = dev_alloc_skb(DUMMY_SKB_SIZE);
	if (skb) {
		struct device *d = &dpriv->pci_priv->pdev->dev;
		int last = dpriv->tx_dirty%TX_RING_SIZE;
		struct TxFD *tx_fd = dpriv->tx_fd + last;
		dma_addr_t addr;

		skb->len = DUMMY_SKB_SIZE;
		skb_copy_to_linear_data(skb, version,
					strlen(version) % DUMMY_SKB_SIZE);
		addr = dma_map_single(d, skb->data, DUMMY_SKB_SIZE,
				      DMA_TO_DEVICE);
		if (dma_mapping_error(d, addr)) {
			dev_kfree_skb_any(skb);
			return NULL;
		}
		tx_fd->state = FrameEnd | TO_STATE_TX(DUMMY_SKB_SIZE);
		tx_fd->data = cpu_to_le32(addr);
		dpriv->tx_skbuff[last] = skb;
	}
	return skb;
}