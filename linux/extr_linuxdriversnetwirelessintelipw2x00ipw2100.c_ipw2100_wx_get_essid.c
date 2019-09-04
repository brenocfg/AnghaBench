#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; int /*<<< orphan*/  length; } ;
union iwreq_data {TYPE_1__ essid; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw2100_priv {int config; int status; int /*<<< orphan*/  essid_len; int /*<<< orphan*/  essid; } ;

/* Variables and functions */
 int CFG_STATIC_ESSID ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,...) ; 
 int STATUS_ASSOCIATED ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipw2100_wx_get_essid(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	/*
	 * This can be called at any time.  No action lock required
	 */

	struct ipw2100_priv *priv = libipw_priv(dev);

	/* If we are associated, trying to associate, or have a statically
	 * configured ESSID then return that; otherwise return ANY */
	if (priv->config & CFG_STATIC_ESSID || priv->status & STATUS_ASSOCIATED) {
		IPW_DEBUG_WX("Getting essid: '%*pE'\n",
			     priv->essid_len, priv->essid);
		memcpy(extra, priv->essid, priv->essid_len);
		wrqu->essid.length = priv->essid_len;
		wrqu->essid.flags = 1;	/* active */
	} else {
		IPW_DEBUG_WX("Getting essid: ANY\n");
		wrqu->essid.length = 0;
		wrqu->essid.flags = 0;	/* active */
	}

	return 0;
}