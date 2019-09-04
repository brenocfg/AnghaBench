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
struct spider_net_descr_chain {int /*<<< orphan*/  lock; TYPE_1__* head; } ;
struct spider_net_card {struct spider_net_descr_chain rx_chain; } ;
struct TYPE_2__ {struct TYPE_2__* next; int /*<<< orphan*/  hwdescr; } ;

/* Variables and functions */
 scalar_t__ SPIDER_NET_DESCR_NOT_IN_USE ; 
 scalar_t__ spider_net_get_descr_status (int /*<<< orphan*/ ) ; 
 scalar_t__ spider_net_prepare_rx_descr (struct spider_net_card*,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_trylock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
spider_net_refill_rx_chain(struct spider_net_card *card)
{
	struct spider_net_descr_chain *chain = &card->rx_chain;
	unsigned long flags;

	/* one context doing the refill (and a second context seeing that
	 * and omitting it) is ok. If called by NAPI, we'll be called again
	 * as spider_net_decode_one_descr is called several times. If some
	 * interrupt calls us, the NAPI is about to clean up anyway. */
	if (!spin_trylock_irqsave(&chain->lock, flags))
		return;

	while (spider_net_get_descr_status(chain->head->hwdescr) ==
			SPIDER_NET_DESCR_NOT_IN_USE) {
		if (spider_net_prepare_rx_descr(card, chain->head))
			break;
		chain->head = chain->head->next;
	}

	spin_unlock_irqrestore(&chain->lock, flags);
}