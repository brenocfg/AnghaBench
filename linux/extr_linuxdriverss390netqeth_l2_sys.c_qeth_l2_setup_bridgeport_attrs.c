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
struct TYPE_4__ {scalar_t__ role; scalar_t__ hostnotification; int /*<<< orphan*/  supported_funcs; } ;
struct TYPE_3__ {TYPE_2__ sbp; } ;
struct qeth_card {TYPE_1__ options; } ;

/* Variables and functions */
 scalar_t__ QETH_SBP_ROLE_NONE ; 
 int qeth_bridgeport_an_set (struct qeth_card*,int) ; 
 int /*<<< orphan*/  qeth_bridgeport_query_ports (struct qeth_card*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_bridgeport_setrole (struct qeth_card*,scalar_t__) ; 

void qeth_l2_setup_bridgeport_attrs(struct qeth_card *card)
{
	int rc;

	if (!card)
		return;
	if (!card->options.sbp.supported_funcs)
		return;
	if (card->options.sbp.role != QETH_SBP_ROLE_NONE) {
		/* Conditional to avoid spurious error messages */
		qeth_bridgeport_setrole(card, card->options.sbp.role);
		/* Let the callback function refresh the stored role value. */
		qeth_bridgeport_query_ports(card,
			&card->options.sbp.role, NULL);
	}
	if (card->options.sbp.hostnotification) {
		rc = qeth_bridgeport_an_set(card, 1);
		if (rc)
			card->options.sbp.hostnotification = 0;
	} else
		qeth_bridgeport_an_set(card, 0);
}