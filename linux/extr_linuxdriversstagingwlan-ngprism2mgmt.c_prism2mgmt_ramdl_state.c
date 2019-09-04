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
struct wlandevice {scalar_t__ msdstate; int /*<<< orphan*/  netdev; struct hfa384x* priv; } ;
struct TYPE_6__ {void* data; void* status; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct p80211msg_p2req_ramdl_state {TYPE_3__ resultcode; TYPE_2__ exeaddr; TYPE_1__ enable; } ;
struct hfa384x {int dummy; } ;

/* Variables and functions */
 void* P80211ENUM_msgitem_status_data_ok ; 
 void* P80211ENUM_resultcode_implementation_failure ; 
 void* P80211ENUM_resultcode_success ; 
 scalar_t__ P80211ENUM_truth_true ; 
 scalar_t__ WLAN_MSD_FWLOAD ; 
 int /*<<< orphan*/  hfa384x_drvr_ramdl_disable (struct hfa384x*) ; 
 scalar_t__ hfa384x_drvr_ramdl_enable (struct hfa384x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

int prism2mgmt_ramdl_state(struct wlandevice *wlandev, void *msgp)
{
	struct hfa384x *hw = wlandev->priv;
	struct p80211msg_p2req_ramdl_state *msg = msgp;

	if (wlandev->msdstate != WLAN_MSD_FWLOAD) {
		netdev_err(wlandev->netdev,
			   "ramdl_state(): may only be called in the fwload state.\n");
		msg->resultcode.data =
		    P80211ENUM_resultcode_implementation_failure;
		msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
		return 0;
	}

	/*
	 ** Note: Interrupts are locked out if this is an AP and are NOT
	 ** locked out if this is a station.
	 */

	msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
	if (msg->enable.data == P80211ENUM_truth_true) {
		if (hfa384x_drvr_ramdl_enable(hw, msg->exeaddr.data)) {
			msg->resultcode.data =
			    P80211ENUM_resultcode_implementation_failure;
		} else {
			msg->resultcode.data = P80211ENUM_resultcode_success;
		}
	} else {
		hfa384x_drvr_ramdl_disable(hw);
		msg->resultcode.data = P80211ENUM_resultcode_success;
	}

	return 0;
}