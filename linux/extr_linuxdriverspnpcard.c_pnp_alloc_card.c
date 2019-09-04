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
struct pnp_protocol {int /*<<< orphan*/  number; int /*<<< orphan*/  dev; } ;
struct pnp_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/ * dma_mask; int /*<<< orphan*/ * parent; } ;
struct pnp_card {int number; TYPE_1__ dev; struct pnp_protocol* protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct pnp_card*) ; 
 struct pnp_card* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct pnp_id* pnp_add_card_id (struct pnp_card*,char*) ; 

struct pnp_card *pnp_alloc_card(struct pnp_protocol *protocol, int id, char *pnpid)
{
	struct pnp_card *card;
	struct pnp_id *dev_id;

	card = kzalloc(sizeof(struct pnp_card), GFP_KERNEL);
	if (!card)
		return NULL;

	card->protocol = protocol;
	card->number = id;

	card->dev.parent = &card->protocol->dev;
	dev_set_name(&card->dev, "%02x:%02x", card->protocol->number, card->number);

	card->dev.coherent_dma_mask = DMA_BIT_MASK(24);
	card->dev.dma_mask = &card->dev.coherent_dma_mask;

	dev_id = pnp_add_card_id(card, pnpid);
	if (!dev_id) {
		kfree(card);
		return NULL;
	}

	return card;
}