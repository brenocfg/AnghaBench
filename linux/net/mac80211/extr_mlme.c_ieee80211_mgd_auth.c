#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_if_managed {struct ieee80211_mgd_auth_data* auth_data; int /*<<< orphan*/  bssid; TYPE_2__* associated; scalar_t__ assoc_data; } ;
struct TYPE_6__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; TYPE_1__ u; } ;
struct ieee80211_mgd_auth_data {int sae_trans; size_t data_len; int key_len; TYPE_4__* bss; scalar_t__ peer_confirmed; int /*<<< orphan*/  algorithm; int /*<<< orphan*/ * key; int /*<<< orphan*/  key_idx; int /*<<< orphan*/ * data; void* sae_status; } ;
struct TYPE_8__ {int /*<<< orphan*/  wiphy; } ;
struct ieee80211_local {int /*<<< orphan*/  mtx; TYPE_3__ hw; } ;
struct cfg80211_auth_request {int auth_type; int auth_data_len; int ie_len; int key_len; TYPE_4__* bss; scalar_t__ key; int /*<<< orphan*/  key_idx; scalar_t__ ie; scalar_t__ auth_data; } ;
typedef  int /*<<< orphan*/  frame_buf ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_9__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_7__ {int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_CHANGED_BSSID ; 
 int EBUSY ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_DEAUTH_FRAME_LEN ; 
 int /*<<< orphan*/  IEEE80211_STYPE_DEAUTH ; 
#define  NL80211_AUTHTYPE_FILS_PK 135 
#define  NL80211_AUTHTYPE_FILS_SK 134 
#define  NL80211_AUTHTYPE_FILS_SK_PFS 133 
#define  NL80211_AUTHTYPE_FT 132 
#define  NL80211_AUTHTYPE_NETWORK_EAP 131 
#define  NL80211_AUTHTYPE_OPEN_SYSTEM 130 
#define  NL80211_AUTHTYPE_SAE 129 
#define  NL80211_AUTHTYPE_SHARED_KEY 128 
 int /*<<< orphan*/  WLAN_AUTH_FILS_PK ; 
 int /*<<< orphan*/  WLAN_AUTH_FILS_SK ; 
 int /*<<< orphan*/  WLAN_AUTH_FILS_SK_PFS ; 
 int /*<<< orphan*/  WLAN_AUTH_FT ; 
 int /*<<< orphan*/  WLAN_AUTH_LEAP ; 
 int /*<<< orphan*/  WLAN_AUTH_OPEN ; 
 int /*<<< orphan*/  WLAN_AUTH_SAE ; 
 int /*<<< orphan*/  WLAN_AUTH_SHARED_KEY ; 
 int /*<<< orphan*/  WLAN_REASON_UNSPECIFIED ; 
 int /*<<< orphan*/  cfg80211_ref_bss (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fips_enabled ; 
 int ieee80211_auth (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_destroy_auth_data (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  ieee80211_mark_sta_auth (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int ieee80211_prep_connection (struct ieee80211_sub_if_data*,TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  ieee80211_report_disconnect (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_set_disassoc (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_vif_release_channel (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_mgd_auth_data*) ; 
 struct ieee80211_mgd_auth_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdata_info (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  sta_info_destroy_addr (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 

int ieee80211_mgd_auth(struct ieee80211_sub_if_data *sdata,
		       struct cfg80211_auth_request *req)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	struct ieee80211_mgd_auth_data *auth_data;
	u16 auth_alg;
	int err;
	bool cont_auth;

	/* prepare auth data structure */

	switch (req->auth_type) {
	case NL80211_AUTHTYPE_OPEN_SYSTEM:
		auth_alg = WLAN_AUTH_OPEN;
		break;
	case NL80211_AUTHTYPE_SHARED_KEY:
		if (fips_enabled)
			return -EOPNOTSUPP;
		auth_alg = WLAN_AUTH_SHARED_KEY;
		break;
	case NL80211_AUTHTYPE_FT:
		auth_alg = WLAN_AUTH_FT;
		break;
	case NL80211_AUTHTYPE_NETWORK_EAP:
		auth_alg = WLAN_AUTH_LEAP;
		break;
	case NL80211_AUTHTYPE_SAE:
		auth_alg = WLAN_AUTH_SAE;
		break;
	case NL80211_AUTHTYPE_FILS_SK:
		auth_alg = WLAN_AUTH_FILS_SK;
		break;
	case NL80211_AUTHTYPE_FILS_SK_PFS:
		auth_alg = WLAN_AUTH_FILS_SK_PFS;
		break;
	case NL80211_AUTHTYPE_FILS_PK:
		auth_alg = WLAN_AUTH_FILS_PK;
		break;
	default:
		return -EOPNOTSUPP;
	}

	if (ifmgd->assoc_data)
		return -EBUSY;

	auth_data = kzalloc(sizeof(*auth_data) + req->auth_data_len +
			    req->ie_len, GFP_KERNEL);
	if (!auth_data)
		return -ENOMEM;

	auth_data->bss = req->bss;

	if (req->auth_data_len >= 4) {
		if (req->auth_type == NL80211_AUTHTYPE_SAE) {
			__le16 *pos = (__le16 *) req->auth_data;

			auth_data->sae_trans = le16_to_cpu(pos[0]);
			auth_data->sae_status = le16_to_cpu(pos[1]);
		}
		memcpy(auth_data->data, req->auth_data + 4,
		       req->auth_data_len - 4);
		auth_data->data_len += req->auth_data_len - 4;
	}

	/* Check if continuing authentication or trying to authenticate with the
	 * same BSS that we were in the process of authenticating with and avoid
	 * removal and re-addition of the STA entry in
	 * ieee80211_prep_connection().
	 */
	cont_auth = ifmgd->auth_data && req->bss == ifmgd->auth_data->bss;

	if (req->ie && req->ie_len) {
		memcpy(&auth_data->data[auth_data->data_len],
		       req->ie, req->ie_len);
		auth_data->data_len += req->ie_len;
	}

	if (req->key && req->key_len) {
		auth_data->key_len = req->key_len;
		auth_data->key_idx = req->key_idx;
		memcpy(auth_data->key, req->key, req->key_len);
	}

	auth_data->algorithm = auth_alg;

	/* try to authenticate/probe */

	if (ifmgd->auth_data) {
		if (cont_auth && req->auth_type == NL80211_AUTHTYPE_SAE) {
			auth_data->peer_confirmed =
				ifmgd->auth_data->peer_confirmed;
		}
		ieee80211_destroy_auth_data(sdata, cont_auth);
	}

	/* prep auth_data so we don't go into idle on disassoc */
	ifmgd->auth_data = auth_data;

	/* If this is continuation of an ongoing SAE authentication exchange
	 * (i.e., request to send SAE Confirm) and the peer has already
	 * confirmed, mark authentication completed since we are about to send
	 * out SAE Confirm.
	 */
	if (cont_auth && req->auth_type == NL80211_AUTHTYPE_SAE &&
	    auth_data->peer_confirmed && auth_data->sae_trans == 2)
		ieee80211_mark_sta_auth(sdata, req->bss->bssid);

	if (ifmgd->associated) {
		u8 frame_buf[IEEE80211_DEAUTH_FRAME_LEN];

		sdata_info(sdata,
			   "disconnect from AP %pM for new auth to %pM\n",
			   ifmgd->associated->bssid, req->bss->bssid);
		ieee80211_set_disassoc(sdata, IEEE80211_STYPE_DEAUTH,
				       WLAN_REASON_UNSPECIFIED,
				       false, frame_buf);

		ieee80211_report_disconnect(sdata, frame_buf,
					    sizeof(frame_buf), true,
					    WLAN_REASON_UNSPECIFIED);
	}

	sdata_info(sdata, "authenticate with %pM\n", req->bss->bssid);

	err = ieee80211_prep_connection(sdata, req->bss, cont_auth, false);
	if (err)
		goto err_clear;

	err = ieee80211_auth(sdata);
	if (err) {
		sta_info_destroy_addr(sdata, req->bss->bssid);
		goto err_clear;
	}

	/* hold our own reference */
	cfg80211_ref_bss(local->hw.wiphy, auth_data->bss);
	return 0;

 err_clear:
	eth_zero_addr(ifmgd->bssid);
	ieee80211_bss_info_change_notify(sdata, BSS_CHANGED_BSSID);
	ifmgd->auth_data = NULL;
	mutex_lock(&sdata->local->mtx);
	ieee80211_vif_release_channel(sdata);
	mutex_unlock(&sdata->local->mtx);
	kfree(auth_data);
	return err;
}