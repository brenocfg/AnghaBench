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
struct lbs_private {int internal_scan; int /*<<< orphan*/  scan_work; int /*<<< orphan*/  work_thread; struct cfg80211_scan_request* scan_req; scalar_t__ scan_channel; } ;
struct cfg80211_scan_request {int /*<<< orphan*/  ie_len; int /*<<< orphan*/  n_channels; int /*<<< orphan*/  n_ssids; } ;

/* Variables and functions */
 int /*<<< orphan*/  lbs_deb_scan (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _internal_start_scan(struct lbs_private *priv, bool internal,
	struct cfg80211_scan_request *request)
{
	lbs_deb_scan("scan: ssids %d, channels %d, ie_len %zd\n",
		request->n_ssids, request->n_channels, request->ie_len);

	priv->scan_channel = 0;
	priv->scan_req = request;
	priv->internal_scan = internal;

	queue_delayed_work(priv->work_thread, &priv->scan_work,
		msecs_to_jiffies(50));
}