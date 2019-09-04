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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct dscc4_dev_priv {struct sk_buff** rx_skbuff; struct sk_buff** tx_skbuff; int /*<<< orphan*/  rx_fd_dma; int /*<<< orphan*/  tx_fd_dma; struct TxFD* rx_fd; struct TxFD* tx_fd; TYPE_2__* pci_priv; } ;
struct device {int dummy; } ;
struct TxFD {int /*<<< orphan*/  data; } ;
struct RxFD {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  HDLC_MAX_MRU ; 
 int /*<<< orphan*/  RX_MAX (int /*<<< orphan*/ ) ; 
 int RX_RING_SIZE ; 
 int /*<<< orphan*/  RX_TOTAL_SIZE ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  TX_TOTAL_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,struct TxFD*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dscc4_release_ring(struct dscc4_dev_priv *dpriv)
{
	struct device *d = &dpriv->pci_priv->pdev->dev;
	struct TxFD *tx_fd = dpriv->tx_fd;
	struct RxFD *rx_fd = dpriv->rx_fd;
	struct sk_buff **skbuff;
	int i;

	dma_free_coherent(d, TX_TOTAL_SIZE, tx_fd, dpriv->tx_fd_dma);
	dma_free_coherent(d, RX_TOTAL_SIZE, rx_fd, dpriv->rx_fd_dma);

	skbuff = dpriv->tx_skbuff;
	for (i = 0; i < TX_RING_SIZE; i++) {
		if (*skbuff) {
			dma_unmap_single(d, le32_to_cpu(tx_fd->data),
					 (*skbuff)->len, DMA_TO_DEVICE);
			dev_kfree_skb(*skbuff);
		}
		skbuff++;
		tx_fd++;
	}

	skbuff = dpriv->rx_skbuff;
	for (i = 0; i < RX_RING_SIZE; i++) {
		if (*skbuff) {
			dma_unmap_single(d, le32_to_cpu(rx_fd->data),
					 RX_MAX(HDLC_MAX_MRU),
					 DMA_FROM_DEVICE);
			dev_kfree_skb(*skbuff);
		}
		skbuff++;
		rx_fd++;
	}
}