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
struct tsi108_prv_data {int rxfree; int rxhead; TYPE_2__* rxring; TYPE_1__* pdev; struct sk_buff** rxskbs; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int misc; int /*<<< orphan*/  blen; int /*<<< orphan*/  buf0; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  TSI108_EC_RXSTAT ; 
 int TSI108_EC_RXSTAT_QUEUE0 ; 
 int /*<<< orphan*/  TSI108_RXBUF_SIZE ; 
 int TSI108_RXRING_LEN ; 
 int TSI108_RX_INT ; 
 int TSI108_RX_OWN ; 
 int /*<<< orphan*/  TSI108_RX_SKB_SIZE ; 
 int TSI_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,int /*<<< orphan*/ ) ; 
 struct tsi108_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tsi108_restart_rx (struct tsi108_prv_data*,struct net_device*) ; 

__attribute__((used)) static int tsi108_refill_rx(struct net_device *dev, int budget)
{
	struct tsi108_prv_data *data = netdev_priv(dev);
	int done = 0;

	while (data->rxfree != TSI108_RXRING_LEN && done != budget) {
		int rx = data->rxhead;
		struct sk_buff *skb;

		skb = netdev_alloc_skb_ip_align(dev, TSI108_RXBUF_SIZE);
		data->rxskbs[rx] = skb;
		if (!skb)
			break;

		data->rxring[rx].buf0 = dma_map_single(&data->pdev->dev,
				skb->data, TSI108_RX_SKB_SIZE,
				DMA_FROM_DEVICE);

		/* Sometimes the hardware sets blen to zero after packet
		 * reception, even though the manual says that it's only ever
		 * modified by the driver.
		 */

		data->rxring[rx].blen = TSI108_RX_SKB_SIZE;
		data->rxring[rx].misc = TSI108_RX_OWN | TSI108_RX_INT;

		data->rxhead = (data->rxhead + 1) % TSI108_RXRING_LEN;
		data->rxfree++;
		done++;
	}

	if (done != 0 && !(TSI_READ(TSI108_EC_RXSTAT) &
			   TSI108_EC_RXSTAT_QUEUE0))
		tsi108_restart_rx(data, dev);

	return done;
}