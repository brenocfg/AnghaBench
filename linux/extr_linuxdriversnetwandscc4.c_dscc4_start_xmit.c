#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_3__ stats; } ;
struct dscc4_dev_priv {int tx_current; int tx_dirty; struct TxFD* tx_fd; struct sk_buff** tx_skbuff; TYPE_2__* pci_priv; } ;
struct device {int dummy; } ;
struct TxFD {int state; int complete; int /*<<< orphan*/  jiffies; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int FrameEnd ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int TO_STATE_TX (int /*<<< orphan*/ ) ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int debug ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dscc4_do_tx (struct dscc4_dev_priv*,struct net_device*) ; 
 struct dscc4_dev_priv* dscc4_priv (struct net_device*) ; 
 int /*<<< orphan*/  dscc4_tx_print (struct net_device*,struct dscc4_dev_priv*,char*) ; 
 scalar_t__ dscc4_tx_quiescent (struct dscc4_dev_priv*,struct net_device*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static netdev_tx_t dscc4_start_xmit(struct sk_buff *skb,
					  struct net_device *dev)
{
	struct dscc4_dev_priv *dpriv = dscc4_priv(dev);
	struct device *d = &dpriv->pci_priv->pdev->dev;
	struct TxFD *tx_fd;
	dma_addr_t addr;
	int next;

	addr = dma_map_single(d, skb->data, skb->len, DMA_TO_DEVICE);
	if (dma_mapping_error(d, addr)) {
		dev_kfree_skb_any(skb);
		dev->stats.tx_dropped++;
		return NETDEV_TX_OK;
	}

	next = dpriv->tx_current%TX_RING_SIZE;
	dpriv->tx_skbuff[next] = skb;
	tx_fd = dpriv->tx_fd + next;
	tx_fd->state = FrameEnd | TO_STATE_TX(skb->len);
	tx_fd->data = cpu_to_le32(addr);
	tx_fd->complete = 0x00000000;
	tx_fd->jiffies = jiffies;
	mb();

#ifdef DSCC4_POLLING
	spin_lock(&dpriv->lock);
	while (dscc4_tx_poll(dpriv, dev));
	spin_unlock(&dpriv->lock);
#endif

	if (debug > 2)
		dscc4_tx_print(dev, dpriv, "Xmit");
	/* To be cleaned(unsigned int)/optimized. Later, ok ? */
	if (!((++dpriv->tx_current - dpriv->tx_dirty)%TX_RING_SIZE))
		netif_stop_queue(dev);

	if (dscc4_tx_quiescent(dpriv, dev))
		dscc4_do_tx(dpriv, dev);

	return NETDEV_TX_OK;
}