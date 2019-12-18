#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ieee802_11_elems {scalar_t__ challenge_len; scalar_t__ challenge; } ;
struct TYPE_6__ {struct ieee80211_mgd_auth_data* auth_data; } ;
struct TYPE_7__ {TYPE_1__ mgd; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; TYPE_2__ u; } ;
struct TYPE_8__ {int /*<<< orphan*/ * variable; } ;
struct TYPE_9__ {TYPE_3__ auth; } ;
struct ieee80211_mgmt {int /*<<< orphan*/  bssid; TYPE_4__ u; } ;
struct ieee80211_mgd_auth_data {int expected_transaction; int /*<<< orphan*/  key_idx; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; TYPE_5__* bss; int /*<<< orphan*/  algorithm; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; } ;
struct TYPE_10__ {int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int IEEE80211_TX_CTL_REQ_TX_STATUS ; 
 int IEEE80211_TX_INTFL_MLME_CONN_TX ; 
 int /*<<< orphan*/  REPORTS_TX_ACK_STATUS ; 
 int /*<<< orphan*/  drv_mgd_prepare_tx (struct ieee80211_local*,struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_hw_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_send_auth (struct ieee80211_sub_if_data*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee802_11_parse_elems (int /*<<< orphan*/ *,size_t,int,struct ieee802_11_elems*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee80211_auth_challenge(struct ieee80211_sub_if_data *sdata,
				     struct ieee80211_mgmt *mgmt, size_t len)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_mgd_auth_data *auth_data = sdata->u.mgd.auth_data;
	u8 *pos;
	struct ieee802_11_elems elems;
	u32 tx_flags = 0;

	pos = mgmt->u.auth.variable;
	ieee802_11_parse_elems(pos, len - (pos - (u8 *)mgmt), false, &elems,
			       mgmt->bssid, auth_data->bss->bssid);
	if (!elems.challenge)
		return;
	auth_data->expected_transaction = 4;
	drv_mgd_prepare_tx(sdata->local, sdata, 0);
	if (ieee80211_hw_check(&local->hw, REPORTS_TX_ACK_STATUS))
		tx_flags = IEEE80211_TX_CTL_REQ_TX_STATUS |
			   IEEE80211_TX_INTFL_MLME_CONN_TX;
	ieee80211_send_auth(sdata, 3, auth_data->algorithm, 0,
			    elems.challenge - 2, elems.challenge_len + 2,
			    auth_data->bss->bssid, auth_data->bss->bssid,
			    auth_data->key, auth_data->key_len,
			    auth_data->key_idx, tx_flags);
}