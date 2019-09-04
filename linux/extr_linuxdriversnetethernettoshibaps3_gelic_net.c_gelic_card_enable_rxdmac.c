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
struct TYPE_4__ {TYPE_1__* head; } ;
struct gelic_card {TYPE_2__ rx_chain; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_id (struct gelic_card*) ; 
 int /*<<< orphan*/  ctodev (struct gelic_card*) ; 
 int /*<<< orphan*/  dev_id (struct gelic_card*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int lv1_net_start_rx_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gelic_card_enable_rxdmac(struct gelic_card *card)
{
	int status;

#ifdef DEBUG
	if (gelic_descr_get_status(card->rx_chain.head) !=
	    GELIC_DESCR_DMA_CARDOWNED) {
		printk(KERN_ERR "%s: status=%x\n", __func__,
		       be32_to_cpu(card->rx_chain.head->dmac_cmd_status));
		printk(KERN_ERR "%s: nextphy=%x\n", __func__,
		       be32_to_cpu(card->rx_chain.head->next_descr_addr));
		printk(KERN_ERR "%s: head=%p\n", __func__,
		       card->rx_chain.head);
	}
#endif
	status = lv1_net_start_rx_dma(bus_id(card), dev_id(card),
				card->rx_chain.head->bus_addr, 0);
	if (status)
		dev_info(ctodev(card),
			 "lv1_net_start_rx_dma failed, status=%d\n", status);
}