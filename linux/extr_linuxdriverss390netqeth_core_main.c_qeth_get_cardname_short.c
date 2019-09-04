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
struct TYPE_2__ {int type; int /*<<< orphan*/  link_type; scalar_t__ guestlan; } ;
struct qeth_card {TYPE_1__ info; } ;

/* Variables and functions */
#define  QETH_CARD_TYPE_IQD 140 
#define  QETH_CARD_TYPE_OSD 139 
#define  QETH_CARD_TYPE_OSM 138 
#define  QETH_CARD_TYPE_OSN 137 
#define  QETH_CARD_TYPE_OSX 136 
#define  QETH_LINK_TYPE_10GBIT_ETH 135 
#define  QETH_LINK_TYPE_FAST_ETH 134 
#define  QETH_LINK_TYPE_GBIT_ETH 133 
#define  QETH_LINK_TYPE_HSTR 132 
#define  QETH_LINK_TYPE_LANE 131 
#define  QETH_LINK_TYPE_LANE_ETH100 130 
#define  QETH_LINK_TYPE_LANE_ETH1000 129 
#define  QETH_LINK_TYPE_LANE_TR 128 

const char *qeth_get_cardname_short(struct qeth_card *card)
{
	if (card->info.guestlan) {
		switch (card->info.type) {
		case QETH_CARD_TYPE_OSD:
			return "Virt.NIC QDIO";
		case QETH_CARD_TYPE_IQD:
			return "Virt.NIC Hiper";
		case QETH_CARD_TYPE_OSM:
			return "Virt.NIC OSM";
		case QETH_CARD_TYPE_OSX:
			return "Virt.NIC OSX";
		default:
			return "unknown";
		}
	} else {
		switch (card->info.type) {
		case QETH_CARD_TYPE_OSD:
			switch (card->info.link_type) {
			case QETH_LINK_TYPE_FAST_ETH:
				return "OSD_100";
			case QETH_LINK_TYPE_HSTR:
				return "HSTR";
			case QETH_LINK_TYPE_GBIT_ETH:
				return "OSD_1000";
			case QETH_LINK_TYPE_10GBIT_ETH:
				return "OSD_10GIG";
			case QETH_LINK_TYPE_LANE_ETH100:
				return "OSD_FE_LANE";
			case QETH_LINK_TYPE_LANE_TR:
				return "OSD_TR_LANE";
			case QETH_LINK_TYPE_LANE_ETH1000:
				return "OSD_GbE_LANE";
			case QETH_LINK_TYPE_LANE:
				return "OSD_ATM_LANE";
			default:
				return "OSD_Express";
			}
		case QETH_CARD_TYPE_IQD:
			return "HiperSockets";
		case QETH_CARD_TYPE_OSN:
			return "OSN";
		case QETH_CARD_TYPE_OSM:
			return "OSM_1000";
		case QETH_CARD_TYPE_OSX:
			return "OSX_10GIG";
		default:
			return "unknown";
		}
	}
	return "n/a";
}