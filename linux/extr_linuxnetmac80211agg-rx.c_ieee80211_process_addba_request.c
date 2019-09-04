#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct sta_info {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  capab; int /*<<< orphan*/  start_seq_num; int /*<<< orphan*/  timeout; int /*<<< orphan*/  dialog_token; } ;
struct TYPE_6__ {TYPE_1__ addba_req; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_3__ action; } ;
struct ieee80211_mgmt {TYPE_4__ u; } ;
struct ieee80211_local {int dummy; } ;

/* Variables and functions */
 int IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK ; 
 int IEEE80211_ADDBA_PARAM_POLICY_MASK ; 
 int IEEE80211_ADDBA_PARAM_TID_MASK ; 
 int /*<<< orphan*/  __ieee80211_start_rx_ba_session (struct sta_info*,int /*<<< orphan*/ ,int,int,int,int,int,int,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

void ieee80211_process_addba_request(struct ieee80211_local *local,
				     struct sta_info *sta,
				     struct ieee80211_mgmt *mgmt,
				     size_t len)
{
	u16 capab, tid, timeout, ba_policy, buf_size, start_seq_num;
	u8 dialog_token;

	/* extract session parameters from addba request frame */
	dialog_token = mgmt->u.action.u.addba_req.dialog_token;
	timeout = le16_to_cpu(mgmt->u.action.u.addba_req.timeout);
	start_seq_num =
		le16_to_cpu(mgmt->u.action.u.addba_req.start_seq_num) >> 4;

	capab = le16_to_cpu(mgmt->u.action.u.addba_req.capab);
	ba_policy = (capab & IEEE80211_ADDBA_PARAM_POLICY_MASK) >> 1;
	tid = (capab & IEEE80211_ADDBA_PARAM_TID_MASK) >> 2;
	buf_size = (capab & IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK) >> 6;

	__ieee80211_start_rx_ba_session(sta, dialog_token, timeout,
					start_seq_num, ba_policy, tid,
					buf_size, true, false);
}