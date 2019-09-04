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
struct TYPE_2__ {scalar_t__ type; scalar_t__ guestlan; } ;
struct qeth_card {TYPE_1__ info; } ;
typedef  enum qeth_discipline_id { ____Placeholder_qeth_discipline_id } qeth_discipline_id ;

/* Variables and functions */
 scalar_t__ QETH_CARD_TYPE_IQD ; 
 scalar_t__ QETH_CARD_TYPE_OSM ; 
 scalar_t__ QETH_CARD_TYPE_OSN ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
#define  QETH_DISCIPLINE_LAYER2 129 
#define  QETH_DISCIPLINE_LAYER3 128 
 int QETH_DISCIPLINE_UNDETERMINED ; 
 int /*<<< orphan*/  SETUP ; 
 int qeth_vm_detect_layer (struct qeth_card*) ; 

__attribute__((used)) static enum qeth_discipline_id qeth_enforce_discipline(struct qeth_card *card)
{
	enum qeth_discipline_id disc = QETH_DISCIPLINE_UNDETERMINED;

	if (card->info.type == QETH_CARD_TYPE_OSM ||
	    card->info.type == QETH_CARD_TYPE_OSN)
		disc = QETH_DISCIPLINE_LAYER2;
	else if (card->info.guestlan)
		disc = (card->info.type == QETH_CARD_TYPE_IQD) ?
				QETH_DISCIPLINE_LAYER3 :
				qeth_vm_detect_layer(card);

	switch (disc) {
	case QETH_DISCIPLINE_LAYER2:
		QETH_DBF_TEXT(SETUP, 3, "force l2");
		break;
	case QETH_DISCIPLINE_LAYER3:
		QETH_DBF_TEXT(SETUP, 3, "force l3");
		break;
	default:
		QETH_DBF_TEXT(SETUP, 3, "force no");
	}

	return disc;
}