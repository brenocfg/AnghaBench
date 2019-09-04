#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gelic_descr_chain {struct gelic_descr* tail; struct gelic_descr* head; } ;
struct gelic_descr {scalar_t__ next_descr_addr; int /*<<< orphan*/  bus_addr; struct gelic_descr* next; } ;
struct gelic_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GELIC_DESCR_DMA_CARDOWNED ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gelic_descr_set_status (struct gelic_descr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gelic_card_reset_chain(struct gelic_card *card,
				   struct gelic_descr_chain *chain,
				   struct gelic_descr *start_descr)
{
	struct gelic_descr *descr;

	for (descr = start_descr; start_descr != descr->next; descr++) {
		gelic_descr_set_status(descr, GELIC_DESCR_DMA_CARDOWNED);
		descr->next_descr_addr = cpu_to_be32(descr->next->bus_addr);
	}

	chain->head = start_descr;
	chain->tail = (descr - 1);

	(descr - 1)->next_descr_addr = 0;
}