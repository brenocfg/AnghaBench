#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int promisc_mode; } ;
struct TYPE_4__ {int role; scalar_t__ reflect_promisc_primary; int /*<<< orphan*/  reflect_promisc; } ;
struct TYPE_5__ {TYPE_1__ sbp; } ;
struct qeth_card {TYPE_3__ info; TYPE_2__ options; struct net_device* dev; } ;
struct net_device {int flags; } ;
typedef  enum qeth_ipa_promisc_modes { ____Placeholder_qeth_ipa_promisc_modes } qeth_ipa_promisc_modes ;

/* Variables and functions */
 int IFF_PROMISC ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,char,int) ; 
 int QETH_SBP_ROLE_NONE ; 
 int QETH_SBP_ROLE_PRIMARY ; 
 int QETH_SBP_ROLE_SECONDARY ; 
 int /*<<< orphan*/  SETUP ; 
 int SET_PROMISC_MODE_OFF ; 
 int SET_PROMISC_MODE_ON ; 
 int qeth_bridgeport_setrole (struct qeth_card*,int) ; 

__attribute__((used)) static void qeth_promisc_to_bridge(struct qeth_card *card)
{
	struct net_device *dev = card->dev;
	enum qeth_ipa_promisc_modes promisc_mode;
	int role;
	int rc;

	QETH_CARD_TEXT(card, 3, "pmisc2br");

	if (!card->options.sbp.reflect_promisc)
		return;
	promisc_mode = (dev->flags & IFF_PROMISC) ? SET_PROMISC_MODE_ON
						: SET_PROMISC_MODE_OFF;
	if (promisc_mode == card->info.promisc_mode)
		return;

	if (promisc_mode == SET_PROMISC_MODE_ON) {
		if (card->options.sbp.reflect_promisc_primary)
			role = QETH_SBP_ROLE_PRIMARY;
		else
			role = QETH_SBP_ROLE_SECONDARY;
	} else
		role = QETH_SBP_ROLE_NONE;

	rc = qeth_bridgeport_setrole(card, role);
	QETH_DBF_TEXT_(SETUP, 2, "bpm%c%04x",
			(promisc_mode == SET_PROMISC_MODE_ON) ? '+' : '-', rc);
	if (!rc) {
		card->options.sbp.role = role;
		card->info.promisc_mode = promisc_mode;
	}

}