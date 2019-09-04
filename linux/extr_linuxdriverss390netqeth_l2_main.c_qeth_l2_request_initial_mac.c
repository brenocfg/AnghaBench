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
struct TYPE_3__ {scalar_t__ type; scalar_t__ guestlan; } ;
struct qeth_card {TYPE_2__* dev; TYPE_1__ info; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int CARD_BUS_ID (struct qeth_card*) ; 
 int EADDRNOTAVAIL ; 
 scalar_t__ MACHINE_IS_VM ; 
 scalar_t__ QETH_CARD_TYPE_IQD ; 
 scalar_t__ QETH_CARD_TYPE_OSM ; 
 scalar_t__ QETH_CARD_TYPE_OSX ; 
 int /*<<< orphan*/  QETH_DBF_HEX (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int,int) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  eth_hw_addr_random (TYPE_2__*) ; 
 int qeth_setadpparms_change_macaddr (struct qeth_card*) ; 
 int qeth_vm_request_mac (struct qeth_card*) ; 

__attribute__((used)) static int qeth_l2_request_initial_mac(struct qeth_card *card)
{
	int rc = 0;

	QETH_DBF_TEXT(SETUP, 2, "l2reqmac");
	QETH_DBF_TEXT_(SETUP, 2, "doL2%s", CARD_BUS_ID(card));

	if (MACHINE_IS_VM) {
		rc = qeth_vm_request_mac(card);
		if (!rc)
			goto out;
		QETH_DBF_MESSAGE(2, "z/VM MAC Service failed on device %s: x%x\n",
				 CARD_BUS_ID(card), rc);
		QETH_DBF_TEXT_(SETUP, 2, "err%04x", rc);
		/* fall back to alternative mechanism: */
	}

	if (card->info.type == QETH_CARD_TYPE_IQD ||
	    card->info.type == QETH_CARD_TYPE_OSM ||
	    card->info.type == QETH_CARD_TYPE_OSX ||
	    card->info.guestlan) {
		rc = qeth_setadpparms_change_macaddr(card);
		if (!rc)
			goto out;
		QETH_DBF_MESSAGE(2, "READ_MAC Assist failed on device %s: x%x\n",
				 CARD_BUS_ID(card), rc);
		QETH_DBF_TEXT_(SETUP, 2, "1err%04x", rc);
		/* fall back once more: */
	}

	/* some devices don't support a custom MAC address: */
	if (card->info.type == QETH_CARD_TYPE_OSM ||
	    card->info.type == QETH_CARD_TYPE_OSX)
		return (rc) ? rc : -EADDRNOTAVAIL;
	eth_hw_addr_random(card->dev);

out:
	QETH_DBF_HEX(SETUP, 2, card->dev->dev_addr, card->dev->addr_len);
	return 0;
}