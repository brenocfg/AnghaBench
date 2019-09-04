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
struct TYPE_2__ {unsigned int sdp_max; unsigned int dcp_max; unsigned int cdp_max; unsigned int aca_max; } ;
struct usb_phy {int chg_type; int /*<<< orphan*/  chg_work; TYPE_1__ chg_cur; } ;

/* Variables and functions */
#define  ACA_TYPE 131 
#define  CDP_TYPE 130 
#define  DCP_TYPE 129 
 unsigned int DEFAULT_ACA_CUR_MAX ; 
 unsigned int DEFAULT_CDP_CUR_MAX ; 
 unsigned int DEFAULT_DCP_CUR_MAX ; 
 unsigned int DEFAULT_SDP_CUR_MAX_SS ; 
#define  SDP_TYPE 128 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void usb_phy_set_charger_current(struct usb_phy *usb_phy, unsigned int mA)
{
	switch (usb_phy->chg_type) {
	case SDP_TYPE:
		if (usb_phy->chg_cur.sdp_max == mA)
			return;

		usb_phy->chg_cur.sdp_max = (mA > DEFAULT_SDP_CUR_MAX_SS) ?
			DEFAULT_SDP_CUR_MAX_SS : mA;
		break;
	case DCP_TYPE:
		if (usb_phy->chg_cur.dcp_max == mA)
			return;

		usb_phy->chg_cur.dcp_max = (mA > DEFAULT_DCP_CUR_MAX) ?
			DEFAULT_DCP_CUR_MAX : mA;
		break;
	case CDP_TYPE:
		if (usb_phy->chg_cur.cdp_max == mA)
			return;

		usb_phy->chg_cur.cdp_max = (mA > DEFAULT_CDP_CUR_MAX) ?
			DEFAULT_CDP_CUR_MAX : mA;
		break;
	case ACA_TYPE:
		if (usb_phy->chg_cur.aca_max == mA)
			return;

		usb_phy->chg_cur.aca_max = (mA > DEFAULT_ACA_CUR_MAX) ?
			DEFAULT_ACA_CUR_MAX : mA;
		break;
	default:
		return;
	}

	schedule_work(&usb_phy->chg_work);
}