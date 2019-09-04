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
struct TYPE_3__ {scalar_t__ cur_chars; int /*<<< orphan*/  rx_bcast_enabled; } ;
struct TYPE_4__ {TYPE_1__ vnicc; } ;
struct qeth_card {TYPE_2__ options; } ;

/* Variables and functions */
 scalar_t__ QETH_VNICC_DEFAULT ; 
 int /*<<< orphan*/  qeth_card_hw_is_reachable (struct qeth_card*) ; 

bool qeth_l2_vnicc_is_in_use(struct qeth_card *card)
{
	/* if everything is turned off, VNICC is not active */
	if (!card->options.vnicc.cur_chars)
		return false;
	/* default values are only OK if rx_bcast was not enabled by user
	 * or the card is offline.
	 */
	if (card->options.vnicc.cur_chars == QETH_VNICC_DEFAULT) {
		if (!card->options.vnicc.rx_bcast_enabled ||
		    !qeth_card_hw_is_reachable(card))
			return false;
	}
	return true;
}