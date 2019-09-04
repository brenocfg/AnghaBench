#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
struct rtllib_device {int proto_stoppping; scalar_t__ state; scalar_t__ iw_mode; scalar_t__ assocresp_ies_len; int /*<<< orphan*/ * assocresp_ies; scalar_t__ assocreq_ies_len; int /*<<< orphan*/ * assocreq_ies; int /*<<< orphan*/  link_change_wq; int /*<<< orphan*/  start_ibss_wq; int /*<<< orphan*/  associate_retry_wq; int /*<<< orphan*/  associate_timer; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* rtllib_ips_leave ) (int /*<<< orphan*/ ) ;scalar_t__ proto_started; } ;

/* Variables and functions */
 scalar_t__ IW_MODE_INFRA ; 
 scalar_t__ RTLLIB_ASSOCIATING_AUTHENTICATED ; 
 scalar_t__ RTLLIB_LINKED ; 
 scalar_t__ RTLLIB_NOLINK ; 
 int /*<<< orphan*/  RemoveAllTS (struct rtllib_device*) ; 
 int /*<<< orphan*/  SendDisassociation (struct rtllib_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtllib_disassociate (struct rtllib_device*) ; 
 int /*<<< orphan*/  rtllib_stop_scan (struct rtllib_device*) ; 
 int /*<<< orphan*/  rtllib_stop_send_beacons (struct rtllib_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void rtllib_stop_protocol(struct rtllib_device *ieee, u8 shutdown)
{
	if (!ieee->proto_started)
		return;

	if (shutdown) {
		ieee->proto_started = 0;
		ieee->proto_stoppping = 1;
		if (ieee->rtllib_ips_leave != NULL)
			ieee->rtllib_ips_leave(ieee->dev);
	}

	rtllib_stop_send_beacons(ieee);
	del_timer_sync(&ieee->associate_timer);
	cancel_delayed_work_sync(&ieee->associate_retry_wq);
	cancel_delayed_work_sync(&ieee->start_ibss_wq);
	cancel_delayed_work_sync(&ieee->link_change_wq);
	rtllib_stop_scan(ieee);

	if (ieee->state <= RTLLIB_ASSOCIATING_AUTHENTICATED)
		ieee->state = RTLLIB_NOLINK;

	if (ieee->state == RTLLIB_LINKED) {
		if (ieee->iw_mode == IW_MODE_INFRA)
			SendDisassociation(ieee, 1, WLAN_REASON_DEAUTH_LEAVING);
		rtllib_disassociate(ieee);
	}

	if (shutdown) {
		RemoveAllTS(ieee);
		ieee->proto_stoppping = 0;
	}
	kfree(ieee->assocreq_ies);
	ieee->assocreq_ies = NULL;
	ieee->assocreq_ies_len = 0;
	kfree(ieee->assocresp_ies);
	ieee->assocresp_ies = NULL;
	ieee->assocresp_ies_len = 0;
}