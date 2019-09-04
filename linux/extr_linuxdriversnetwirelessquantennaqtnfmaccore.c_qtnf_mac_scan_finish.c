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
struct qtnf_wmac {int /*<<< orphan*/  mac_lock; int /*<<< orphan*/ * scan_req; } ;
struct cfg80211_scan_info {int aborted; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfg80211_scan_done (int /*<<< orphan*/ *,struct cfg80211_scan_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qtnf_mac_scan_finish(struct qtnf_wmac *mac, bool aborted)
{
	struct cfg80211_scan_info info = {
		.aborted = aborted,
	};

	mutex_lock(&mac->mac_lock);

	if (mac->scan_req) {
		cfg80211_scan_done(mac->scan_req, &info);
		mac->scan_req = NULL;
	}

	mutex_unlock(&mac->mac_lock);
}