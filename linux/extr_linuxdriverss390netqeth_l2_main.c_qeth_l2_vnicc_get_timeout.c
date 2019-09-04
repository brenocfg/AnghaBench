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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int sup_chars; int getset_timeout_sup; int /*<<< orphan*/  learning_timeout; } ;
struct TYPE_4__ {TYPE_1__ vnicc; } ;
struct qeth_card {TYPE_2__ options; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IPA_VNICC_GET_TIMEOUT ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int QETH_VNICC_LEARNING ; 
 scalar_t__ qeth_bridgeport_is_in_use (struct qeth_card*) ; 
 scalar_t__ qeth_card_hw_is_reachable (struct qeth_card*) ; 
 int qeth_l2_vnicc_getset_timeout (struct qeth_card*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qeth_l2_vnicc_get_timeout(struct qeth_card *card, u32 *timeout)
{
	int rc = 0;

	QETH_CARD_TEXT(card, 2, "vniccgto");

	/* do not get anything if BridgePort is enabled */
	if (qeth_bridgeport_is_in_use(card))
		return -EBUSY;

	/* check if characteristic and get_timeout are supported */
	if (!(card->options.vnicc.sup_chars & QETH_VNICC_LEARNING) ||
	    !(card->options.vnicc.getset_timeout_sup & QETH_VNICC_LEARNING))
		return -EOPNOTSUPP;
	/* if card is ready, get timeout. Otherwise, just return stored value */
	*timeout = card->options.vnicc.learning_timeout;
	if (qeth_card_hw_is_reachable(card))
		rc = qeth_l2_vnicc_getset_timeout(card, QETH_VNICC_LEARNING,
						  IPA_VNICC_GET_TIMEOUT,
						  timeout);

	return rc;
}