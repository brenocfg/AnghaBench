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
struct wiphy {int features; } ;
struct TYPE_7__ {int /*<<< orphan*/  beacon; } ;
struct TYPE_8__ {TYPE_3__ ap; } ;
struct ieee80211_sub_if_data {TYPE_4__ u; TYPE_2__* local; int /*<<< orphan*/  vif; } ;
struct cfg80211_scan_request {int flags; int /*<<< orphan*/  wdev; } ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  hw_scan; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct ieee80211_sub_if_data* IEEE80211_WDEV_TO_SUB_IF (int /*<<< orphan*/ ) ; 
 int NL80211_FEATURE_AP_SCAN ; 
#define  NL80211_IFTYPE_ADHOC 135 
#define  NL80211_IFTYPE_AP 134 
#define  NL80211_IFTYPE_MESH_POINT 133 
#define  NL80211_IFTYPE_NAN 132 
#define  NL80211_IFTYPE_P2P_CLIENT 131 
#define  NL80211_IFTYPE_P2P_DEVICE 130 
#define  NL80211_IFTYPE_P2P_GO 129 
#define  NL80211_IFTYPE_STATION 128 
 int NL80211_SCAN_FLAG_AP ; 
 int ieee80211_request_scan (struct ieee80211_sub_if_data*,struct cfg80211_scan_request*) ; 
 int ieee80211_vif_type_p2p (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ieee80211_scan(struct wiphy *wiphy,
			  struct cfg80211_scan_request *req)
{
	struct ieee80211_sub_if_data *sdata;

	sdata = IEEE80211_WDEV_TO_SUB_IF(req->wdev);

	switch (ieee80211_vif_type_p2p(&sdata->vif)) {
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_ADHOC:
	case NL80211_IFTYPE_MESH_POINT:
	case NL80211_IFTYPE_P2P_CLIENT:
	case NL80211_IFTYPE_P2P_DEVICE:
		break;
	case NL80211_IFTYPE_P2P_GO:
		if (sdata->local->ops->hw_scan)
			break;
		/*
		 * FIXME: implement NoA while scanning in software,
		 * for now fall through to allow scanning only when
		 * beaconing hasn't been configured yet
		 */
		/* fall through */
	case NL80211_IFTYPE_AP:
		/*
		 * If the scan has been forced (and the driver supports
		 * forcing), don't care about being beaconing already.
		 * This will create problems to the attached stations (e.g. all
		 * the  frames sent while scanning on other channel will be
		 * lost)
		 */
		if (sdata->u.ap.beacon &&
		    (!(wiphy->features & NL80211_FEATURE_AP_SCAN) ||
		     !(req->flags & NL80211_SCAN_FLAG_AP)))
			return -EOPNOTSUPP;
		break;
	case NL80211_IFTYPE_NAN:
	default:
		return -EOPNOTSUPP;
	}

	return ieee80211_request_scan(sdata, req);
}