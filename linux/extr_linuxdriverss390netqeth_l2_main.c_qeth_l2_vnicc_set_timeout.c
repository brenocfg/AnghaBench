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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int sup_chars; int getset_timeout_sup; scalar_t__ learning_timeout; } ;
struct TYPE_3__ {TYPE_2__ vnicc; } ;
struct qeth_card {TYPE_1__ options; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IPA_VNICC_SET_TIMEOUT ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int QETH_VNICC_LEARNING ; 
 scalar_t__ qeth_bridgeport_is_in_use (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_card_hw_is_reachable (struct qeth_card*) ; 
 int qeth_l2_vnicc_getset_timeout (struct qeth_card*,int,int /*<<< orphan*/ ,scalar_t__*) ; 

int qeth_l2_vnicc_set_timeout(struct qeth_card *card, u32 timeout)
{
	int rc = 0;

	QETH_CARD_TEXT(card, 2, "vniccsto");

	/* do not change anything if BridgePort is enabled */
	if (qeth_bridgeport_is_in_use(card))
		return -EBUSY;

	/* check if characteristic and set_timeout are supported */
	if (!(card->options.vnicc.sup_chars & QETH_VNICC_LEARNING) ||
	    !(card->options.vnicc.getset_timeout_sup & QETH_VNICC_LEARNING))
		return -EOPNOTSUPP;

	/* do we need to do anything? */
	if (card->options.vnicc.learning_timeout == timeout)
		return rc;

	/* if card is not ready, simply store the value internally and return */
	if (!qeth_card_hw_is_reachable(card)) {
		card->options.vnicc.learning_timeout = timeout;
		return rc;
	}

	/* send timeout value to card; if successful, store value internally */
	rc = qeth_l2_vnicc_getset_timeout(card, QETH_VNICC_LEARNING,
					  IPA_VNICC_SET_TIMEOUT, &timeout);
	if (!rc)
		card->options.vnicc.learning_timeout = timeout;

	return rc;
}