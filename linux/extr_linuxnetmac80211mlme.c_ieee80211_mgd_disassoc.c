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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_if_managed {TYPE_2__* associated; } ;
struct TYPE_3__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {TYPE_1__ u; } ;
struct cfg80211_disassoc_request {int /*<<< orphan*/  reason_code; int /*<<< orphan*/  local_state_change; TYPE_2__* bss; } ;
typedef  int /*<<< orphan*/  frame_buf ;
struct TYPE_4__ {int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int ENOLINK ; 
 int ETH_ALEN ; 
 int IEEE80211_DEAUTH_FRAME_LEN ; 
 int /*<<< orphan*/  IEEE80211_STYPE_DISASSOC ; 
 int /*<<< orphan*/  ieee80211_get_reason_code_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_report_disconnect (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_set_disassoc (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdata_info (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ieee80211_mgd_disassoc(struct ieee80211_sub_if_data *sdata,
			   struct cfg80211_disassoc_request *req)
{
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	u8 bssid[ETH_ALEN];
	u8 frame_buf[IEEE80211_DEAUTH_FRAME_LEN];

	/*
	 * cfg80211 should catch this ... but it's racy since
	 * we can receive a disassoc frame, process it, hand it
	 * to cfg80211 while that's in a locked section already
	 * trying to tell us that the user wants to disconnect.
	 */
	if (ifmgd->associated != req->bss)
		return -ENOLINK;

	sdata_info(sdata,
		   "disassociating from %pM by local choice (Reason: %u=%s)\n",
		   req->bss->bssid, req->reason_code, ieee80211_get_reason_code_string(req->reason_code));

	memcpy(bssid, req->bss->bssid, ETH_ALEN);
	ieee80211_set_disassoc(sdata, IEEE80211_STYPE_DISASSOC,
			       req->reason_code, !req->local_state_change,
			       frame_buf);

	ieee80211_report_disconnect(sdata, frame_buf, sizeof(frame_buf), true,
				    req->reason_code);

	return 0;
}