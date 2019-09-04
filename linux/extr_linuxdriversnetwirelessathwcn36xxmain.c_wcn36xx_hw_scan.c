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
struct wcn36xx {int scan_aborted; int /*<<< orphan*/  scan_work; int /*<<< orphan*/  fw_feat_caps; int /*<<< orphan*/  scan_lock; int /*<<< orphan*/ * scan_req; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_scan_request {int /*<<< orphan*/  req; } ;
struct ieee80211_hw {struct wcn36xx* priv; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SCAN_OFFLOAD ; 
 int /*<<< orphan*/  get_feat_caps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int wcn36xx_smd_start_hw_scan (struct wcn36xx*,struct ieee80211_vif*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wcn36xx_hw_scan(struct ieee80211_hw *hw,
			   struct ieee80211_vif *vif,
			   struct ieee80211_scan_request *hw_req)
{
	struct wcn36xx *wcn = hw->priv;
	mutex_lock(&wcn->scan_lock);
	if (wcn->scan_req) {
		mutex_unlock(&wcn->scan_lock);
		return -EBUSY;
	}

	wcn->scan_aborted = false;
	wcn->scan_req = &hw_req->req;

	mutex_unlock(&wcn->scan_lock);

	if (!get_feat_caps(wcn->fw_feat_caps, SCAN_OFFLOAD)) {
		/* legacy manual/sw scan */
		schedule_work(&wcn->scan_work);
		return 0;
	}

	return wcn36xx_smd_start_hw_scan(wcn, vif, &hw_req->req);
}