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
struct spider_net_hw_descr {scalar_t__ next_descr_addr; int /*<<< orphan*/  dmac_cmd_status; } ;
struct spider_net_descr_chain {int num_desc; int dma_addr; struct spider_net_descr* ring; struct spider_net_descr* tail; struct spider_net_descr* head; int /*<<< orphan*/  lock; struct spider_net_hw_descr* hwring; } ;
struct spider_net_descr {int bus_addr; struct spider_net_descr* prev; struct spider_net_descr* next; struct spider_net_hw_descr* hwdescr; } ;
struct spider_net_card {TYPE_1__* pdev; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SPIDER_NET_DESCR_NOT_IN_USE ; 
 struct spider_net_hw_descr* dma_alloc_coherent (int /*<<< orphan*/ *,size_t,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct spider_net_descr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
spider_net_init_chain(struct spider_net_card *card,
		       struct spider_net_descr_chain *chain)
{
	int i;
	struct spider_net_descr *descr;
	struct spider_net_hw_descr *hwdescr;
	dma_addr_t buf;
	size_t alloc_size;

	alloc_size = chain->num_desc * sizeof(struct spider_net_hw_descr);

	chain->hwring = dma_alloc_coherent(&card->pdev->dev, alloc_size,
					   &chain->dma_addr, GFP_KERNEL);
	if (!chain->hwring)
		return -ENOMEM;

	memset(chain->ring, 0, chain->num_desc * sizeof(struct spider_net_descr));

	/* Set up the hardware pointers in each descriptor */
	descr = chain->ring;
	hwdescr = chain->hwring;
	buf = chain->dma_addr;
	for (i=0; i < chain->num_desc; i++, descr++, hwdescr++) {
		hwdescr->dmac_cmd_status = SPIDER_NET_DESCR_NOT_IN_USE;
		hwdescr->next_descr_addr = 0;

		descr->hwdescr = hwdescr;
		descr->bus_addr = buf;
		descr->next = descr + 1;
		descr->prev = descr - 1;

		buf += sizeof(struct spider_net_hw_descr);
	}
	/* do actual circular list */
	(descr-1)->next = chain->ring;
	chain->ring->prev = descr-1;

	spin_lock_init(&chain->lock);
	chain->head = chain->ring;
	chain->tail = chain->ring;
	return 0;
}