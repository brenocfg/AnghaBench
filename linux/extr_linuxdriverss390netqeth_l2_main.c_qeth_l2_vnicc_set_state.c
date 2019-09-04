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
typedef  int u32 ;
struct TYPE_3__ {int sup_chars; int set_char_sup; int wanted_chars; int cur_chars; int rx_bcast_enabled; int /*<<< orphan*/  learning_timeout; } ;
struct TYPE_4__ {TYPE_1__ vnicc; } ;
struct qeth_card {TYPE_2__ options; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int IPA_VNICC_DISABLE ; 
 int IPA_VNICC_ENABLE ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int QETH_VNICC_LEARNING ; 
 int QETH_VNICC_RX_BCAST ; 
 scalar_t__ qeth_bridgeport_is_in_use (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_card_hw_is_reachable (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l2_vnicc_recover_timeout (struct qeth_card*,int,int /*<<< orphan*/ *) ; 
 int qeth_l2_vnicc_set_char (struct qeth_card*,int,int) ; 

int qeth_l2_vnicc_set_state(struct qeth_card *card, u32 vnicc, bool state)
{
	int rc = 0;
	u32 cmd;

	QETH_CARD_TEXT(card, 2, "vniccsch");

	/* do not change anything if BridgePort is enabled */
	if (qeth_bridgeport_is_in_use(card))
		return -EBUSY;

	/* check if characteristic and enable/disable are supported */
	if (!(card->options.vnicc.sup_chars & vnicc) ||
	    !(card->options.vnicc.set_char_sup & vnicc))
		return -EOPNOTSUPP;

	/* set enable/disable command and store wanted characteristic */
	if (state) {
		cmd = IPA_VNICC_ENABLE;
		card->options.vnicc.wanted_chars |= vnicc;
	} else {
		cmd = IPA_VNICC_DISABLE;
		card->options.vnicc.wanted_chars &= ~vnicc;
	}

	/* do we need to do anything? */
	if (card->options.vnicc.cur_chars == card->options.vnicc.wanted_chars)
		return rc;

	/* if card is not ready, simply stop here */
	if (!qeth_card_hw_is_reachable(card)) {
		if (state)
			card->options.vnicc.cur_chars |= vnicc;
		else
			card->options.vnicc.cur_chars &= ~vnicc;
		return rc;
	}

	rc = qeth_l2_vnicc_set_char(card, vnicc, cmd);
	if (rc)
		card->options.vnicc.wanted_chars =
			card->options.vnicc.cur_chars;
	else {
		/* successful online VNICC change; handle special cases */
		if (state && vnicc == QETH_VNICC_RX_BCAST)
			card->options.vnicc.rx_bcast_enabled = true;
		if (!state && vnicc == QETH_VNICC_LEARNING)
			qeth_l2_vnicc_recover_timeout(card, vnicc,
					&card->options.vnicc.learning_timeout);
	}

	return rc;
}