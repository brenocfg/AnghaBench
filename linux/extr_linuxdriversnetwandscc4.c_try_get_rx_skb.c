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
struct sk_buff {int /*<<< orphan*/  data; int /*<<< orphan*/  protocol; } ;
struct net_device {int dummy; } ;
struct dscc4_dev_priv {unsigned int rx_dirty; struct sk_buff** rx_skbuff; struct RxFD* rx_fd; TYPE_2__* pci_priv; } ;
struct device {int dummy; } ;
struct RxFD {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  HDLC_MAX_MRU ; 
 int RX_MAX (int /*<<< orphan*/ ) ; 
 unsigned int RX_RING_SIZE ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (int const) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdlc_type_trans (struct sk_buff*,struct net_device*) ; 

__attribute__((used)) static inline int try_get_rx_skb(struct dscc4_dev_priv *dpriv,
				 struct net_device *dev)
{
	unsigned int dirty = dpriv->rx_dirty%RX_RING_SIZE;
	struct device *d = &dpriv->pci_priv->pdev->dev;
	struct RxFD *rx_fd = dpriv->rx_fd + dirty;
	const int len = RX_MAX(HDLC_MAX_MRU);
	struct sk_buff *skb;
	dma_addr_t addr;

	skb = dev_alloc_skb(len);
	if (!skb)
		goto err_out;

	skb->protocol = hdlc_type_trans(skb, dev);
	addr = dma_map_single(d, skb->data, len, DMA_FROM_DEVICE);
	if (dma_mapping_error(d, addr))
		goto err_free_skb;

	dpriv->rx_skbuff[dirty] = skb;
	rx_fd->data = cpu_to_le32(addr);
	return 0;

err_free_skb:
	dev_kfree_skb_any(skb);
err_out:
	rx_fd->data = 0;
	return -1;
}