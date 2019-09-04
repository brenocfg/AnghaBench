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
struct wiphy {int dummy; } ;
struct orinoco_private {struct cfg80211_scan_request* scan_request; } ;
struct cfg80211_scan_request {int /*<<< orphan*/  ssids; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int orinoco_hw_trigger_scan (struct orinoco_private*,int /*<<< orphan*/ ) ; 
 struct orinoco_private* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int orinoco_scan(struct wiphy *wiphy,
			struct cfg80211_scan_request *request)
{
	struct orinoco_private *priv = wiphy_priv(wiphy);
	int err;

	if (!request)
		return -EINVAL;

	if (priv->scan_request && priv->scan_request != request)
		return -EBUSY;

	priv->scan_request = request;

	err = orinoco_hw_trigger_scan(priv, request->ssids);
	/* On error the we aren't processing the request */
	if (err)
		priv->scan_request = NULL;

	return err;
}