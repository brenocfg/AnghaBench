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
struct TYPE_2__ {int type; scalar_t__ guestlan; } ;
struct qeth_card {TYPE_1__ info; } ;

/* Variables and functions */
#define  QETH_CARD_TYPE_IQD 132 
#define  QETH_CARD_TYPE_OSD 131 
#define  QETH_CARD_TYPE_OSM 130 
#define  QETH_CARD_TYPE_OSN 129 
#define  QETH_CARD_TYPE_OSX 128 

__attribute__((used)) static const char *qeth_get_cardname(struct qeth_card *card)
{
	if (card->info.guestlan) {
		switch (card->info.type) {
		case QETH_CARD_TYPE_OSD:
			return " Virtual NIC QDIO";
		case QETH_CARD_TYPE_IQD:
			return " Virtual NIC Hiper";
		case QETH_CARD_TYPE_OSM:
			return " Virtual NIC QDIO - OSM";
		case QETH_CARD_TYPE_OSX:
			return " Virtual NIC QDIO - OSX";
		default:
			return " unknown";
		}
	} else {
		switch (card->info.type) {
		case QETH_CARD_TYPE_OSD:
			return " OSD Express";
		case QETH_CARD_TYPE_IQD:
			return " HiperSockets";
		case QETH_CARD_TYPE_OSN:
			return " OSN QDIO";
		case QETH_CARD_TYPE_OSM:
			return " OSM QDIO";
		case QETH_CARD_TYPE_OSX:
			return " OSX QDIO";
		default:
			return " unknown";
		}
	}
	return " n/a";
}