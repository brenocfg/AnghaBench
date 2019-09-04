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
struct spider_net_descr {struct spider_net_descr* next; int /*<<< orphan*/ * skb; TYPE_2__* hwdescr; } ;
struct TYPE_3__ {struct spider_net_descr* head; } ;
struct spider_net_card {int /*<<< orphan*/  pdev; TYPE_1__ rx_chain; } ;
struct TYPE_4__ {int /*<<< orphan*/  buf_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  SPIDER_NET_MAX_FRAME ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spider_net_free_rx_chain_contents(struct spider_net_card *card)
{
	struct spider_net_descr *descr;

	descr = card->rx_chain.head;
	do {
		if (descr->skb) {
			pci_unmap_single(card->pdev, descr->hwdescr->buf_addr,
					 SPIDER_NET_MAX_FRAME,
					 PCI_DMA_BIDIRECTIONAL);
			dev_kfree_skb(descr->skb);
			descr->skb = NULL;
		}
		descr = descr->next;
	} while (descr != card->rx_chain.head);
}