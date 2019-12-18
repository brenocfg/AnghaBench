#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_if_managed {TYPE_6__* associated; TYPE_5__* assoc_data; TYPE_3__* auth_data; } ;
struct TYPE_7__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  local; TYPE_1__ u; } ;
struct cfg80211_deauth_request {int /*<<< orphan*/  reason_code; int /*<<< orphan*/  bssid; int /*<<< orphan*/  local_state_change; } ;
typedef  int /*<<< orphan*/  frame_buf ;
struct TYPE_12__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_11__ {TYPE_4__* bss; } ;
struct TYPE_10__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_9__ {TYPE_2__* bss; } ;
struct TYPE_8__ {int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int ENOTCONN ; 
 int IEEE80211_DEAUTH_FRAME_LEN ; 
 int /*<<< orphan*/  IEEE80211_STYPE_DEAUTH ; 
 int /*<<< orphan*/  drv_mgd_prepare_tx (int /*<<< orphan*/ ,struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_destroy_assoc_data (struct ieee80211_sub_if_data*,int,int) ; 
 int /*<<< orphan*/  ieee80211_destroy_auth_data (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  ieee80211_get_reason_code_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_report_disconnect (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_send_deauth_disassoc (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_set_disassoc (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdata_info (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ieee80211_mgd_deauth(struct ieee80211_sub_if_data *sdata,
			 struct cfg80211_deauth_request *req)
{
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	u8 frame_buf[IEEE80211_DEAUTH_FRAME_LEN];
	bool tx = !req->local_state_change;

	if (ifmgd->auth_data &&
	    ether_addr_equal(ifmgd->auth_data->bss->bssid, req->bssid)) {
		sdata_info(sdata,
			   "aborting authentication with %pM by local choice (Reason: %u=%s)\n",
			   req->bssid, req->reason_code,
			   ieee80211_get_reason_code_string(req->reason_code));

		drv_mgd_prepare_tx(sdata->local, sdata, 0);
		ieee80211_send_deauth_disassoc(sdata, req->bssid, req->bssid,
					       IEEE80211_STYPE_DEAUTH,
					       req->reason_code, tx,
					       frame_buf);
		ieee80211_destroy_auth_data(sdata, false);
		ieee80211_report_disconnect(sdata, frame_buf,
					    sizeof(frame_buf), true,
					    req->reason_code);

		return 0;
	}

	if (ifmgd->assoc_data &&
	    ether_addr_equal(ifmgd->assoc_data->bss->bssid, req->bssid)) {
		sdata_info(sdata,
			   "aborting association with %pM by local choice (Reason: %u=%s)\n",
			   req->bssid, req->reason_code,
			   ieee80211_get_reason_code_string(req->reason_code));

		drv_mgd_prepare_tx(sdata->local, sdata, 0);
		ieee80211_send_deauth_disassoc(sdata, req->bssid, req->bssid,
					       IEEE80211_STYPE_DEAUTH,
					       req->reason_code, tx,
					       frame_buf);
		ieee80211_destroy_assoc_data(sdata, false, true);
		ieee80211_report_disconnect(sdata, frame_buf,
					    sizeof(frame_buf), true,
					    req->reason_code);
		return 0;
	}

	if (ifmgd->associated &&
	    ether_addr_equal(ifmgd->associated->bssid, req->bssid)) {
		sdata_info(sdata,
			   "deauthenticating from %pM by local choice (Reason: %u=%s)\n",
			   req->bssid, req->reason_code,
			   ieee80211_get_reason_code_string(req->reason_code));

		ieee80211_set_disassoc(sdata, IEEE80211_STYPE_DEAUTH,
				       req->reason_code, tx, frame_buf);
		ieee80211_report_disconnect(sdata, frame_buf,
					    sizeof(frame_buf), true,
					    req->reason_code);
		return 0;
	}

	return -ENOTCONN;
}