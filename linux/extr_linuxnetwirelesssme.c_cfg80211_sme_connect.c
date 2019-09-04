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
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  struct cfg80211_connect_params {scalar_t__ auth_type; int /*<<< orphan*/  ie_len; int /*<<< orphan*/  ie; struct cfg80211_connect_params const* bssid; } const cfg80211_connect_params ;
typedef  struct cfg80211_connect_params u8 ;
struct wireless_dev {TYPE_3__* conn; int /*<<< orphan*/  wiphy; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; TYPE_5__* current_bss; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct cfg80211_bss {int dummy; } ;
typedef  enum nl80211_timeout_reason { ____Placeholder_nl80211_timeout_reason } nl80211_timeout_reason ;
struct TYPE_10__ {struct cfg80211_bss pub; } ;
struct TYPE_8__ {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  auth_type; int /*<<< orphan*/  ie; int /*<<< orphan*/  ie_len; struct TYPE_8__* bssid; } ;
struct TYPE_9__ {int auto_auth; int prev_bssid_valid; int /*<<< orphan*/  state; TYPE_2__* prev_bssid; TYPE_2__ params; int /*<<< orphan*/  ie; TYPE_2__* bssid; } ;
struct TYPE_7__ {int /*<<< orphan*/  assoc; int /*<<< orphan*/  auth; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG80211_CONN_SCAN_AGAIN ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NL80211_AUTHTYPE_AUTOMATIC ; 
 int /*<<< orphan*/  NL80211_AUTHTYPE_OPEN_SYSTEM ; 
 scalar_t__ WARN_ON (TYPE_3__*) ; 
 int cfg80211_conn_do_work (struct wireless_dev*,int*) ; 
 int cfg80211_conn_scan (struct wireless_dev*) ; 
 struct cfg80211_bss* cfg80211_get_conn_bss (struct wireless_dev*) ; 
 int /*<<< orphan*/  cfg80211_put_bss (int /*<<< orphan*/ ,struct cfg80211_bss*) ; 
 int /*<<< orphan*/  cfg80211_sme_free (struct wireless_dev*) ; 
 scalar_t__ cfg80211_sme_get_conn_ies (struct wireless_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfg80211_unhold_bss (TYPE_5__*) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 TYPE_3__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,struct cfg80211_connect_params const*,int) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfg80211_sme_connect(struct wireless_dev *wdev,
				struct cfg80211_connect_params *connect,
				const u8 *prev_bssid)
{
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);
	struct cfg80211_bss *bss;
	int err;

	if (!rdev->ops->auth || !rdev->ops->assoc)
		return -EOPNOTSUPP;

	if (wdev->current_bss) {
		cfg80211_unhold_bss(wdev->current_bss);
		cfg80211_put_bss(wdev->wiphy, &wdev->current_bss->pub);
		wdev->current_bss = NULL;

		cfg80211_sme_free(wdev);
	}

	if (WARN_ON(wdev->conn))
		return -EINPROGRESS;

	wdev->conn = kzalloc(sizeof(*wdev->conn), GFP_KERNEL);
	if (!wdev->conn)
		return -ENOMEM;

	/*
	 * Copy all parameters, and treat explicitly IEs, BSSID, SSID.
	 */
	memcpy(&wdev->conn->params, connect, sizeof(*connect));
	if (connect->bssid) {
		wdev->conn->params.bssid = wdev->conn->bssid;
		memcpy(wdev->conn->bssid, connect->bssid, ETH_ALEN);
	}

	if (cfg80211_sme_get_conn_ies(wdev, connect->ie, connect->ie_len,
				      &wdev->conn->ie,
				      &wdev->conn->params.ie_len)) {
		kfree(wdev->conn);
		wdev->conn = NULL;
		return -ENOMEM;
	}
	wdev->conn->params.ie = wdev->conn->ie;

	if (connect->auth_type == NL80211_AUTHTYPE_AUTOMATIC) {
		wdev->conn->auto_auth = true;
		/* start with open system ... should mostly work */
		wdev->conn->params.auth_type =
			NL80211_AUTHTYPE_OPEN_SYSTEM;
	} else {
		wdev->conn->auto_auth = false;
	}

	wdev->conn->params.ssid = wdev->ssid;
	wdev->conn->params.ssid_len = wdev->ssid_len;

	/* see if we have the bss already */
	bss = cfg80211_get_conn_bss(wdev);

	if (prev_bssid) {
		memcpy(wdev->conn->prev_bssid, prev_bssid, ETH_ALEN);
		wdev->conn->prev_bssid_valid = true;
	}

	/* we're good if we have a matching bss struct */
	if (bss) {
		enum nl80211_timeout_reason treason;

		err = cfg80211_conn_do_work(wdev, &treason);
		cfg80211_put_bss(wdev->wiphy, bss);
	} else {
		/* otherwise we'll need to scan for the AP first */
		err = cfg80211_conn_scan(wdev);

		/*
		 * If we can't scan right now, then we need to scan again
		 * after the current scan finished, since the parameters
		 * changed (unless we find a good AP anyway).
		 */
		if (err == -EBUSY) {
			err = 0;
			wdev->conn->state = CFG80211_CONN_SCAN_AGAIN;
		}
	}

	if (err)
		cfg80211_sme_free(wdev);

	return err;
}