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
struct rtllib_device {scalar_t__ sta_sleep; int ack_tx_to_ieee; int polling; TYPE_1__* pHTInfo; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* sta_wake_up ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int IOTAction; } ;

/* Variables and functions */
 int HT_IOT_ACT_NULL_DATA_POWER_SAVING ; 
 scalar_t__ LPS_IS_SLEEP ; 
 scalar_t__ LPS_IS_WAKE ; 
 int /*<<< orphan*/  rtllib_sta_ps_send_null_frame (struct rtllib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtllib_sta_ps_send_pspoll_frame (struct rtllib_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtllib_sta_wakeup(struct rtllib_device *ieee, short nl)
{
	if (ieee->sta_sleep == LPS_IS_WAKE) {
		if (nl) {
			if (ieee->pHTInfo->IOTAction &
			    HT_IOT_ACT_NULL_DATA_POWER_SAVING) {
				ieee->ack_tx_to_ieee = 1;
				rtllib_sta_ps_send_null_frame(ieee, 0);
			} else {
				ieee->ack_tx_to_ieee = 1;
				rtllib_sta_ps_send_pspoll_frame(ieee);
			}
		}
		return;

	}

	if (ieee->sta_sleep == LPS_IS_SLEEP)
		ieee->sta_wake_up(ieee->dev);
	if (nl) {
		if (ieee->pHTInfo->IOTAction &
		    HT_IOT_ACT_NULL_DATA_POWER_SAVING) {
			ieee->ack_tx_to_ieee = 1;
			rtllib_sta_ps_send_null_frame(ieee, 0);
		} else {
			ieee->ack_tx_to_ieee = 1;
			ieee->polling = true;
			rtllib_sta_ps_send_pspoll_frame(ieee);
		}

	} else {
		ieee->sta_sleep = LPS_IS_WAKE;
		ieee->polling = false;
	}
}