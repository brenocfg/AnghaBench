#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ length; int flags; } ;
union iwreq_data {TYPE_3__ essid; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/  body; } ;
struct TYPE_5__ {TYPE_1__ ssid; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; TYPE_2__ reg; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ SLP_SLEEP ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_get_essid(struct net_device *dev,
			     struct iw_request_info *info,
			     union iwreq_data *dwrq, char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;

	/* for SLEEP MODE */
	/* Note : if dwrq->flags != 0, we should
	 * get the relevant SSID from the SSID list...
	 */
	if (priv->reg.ssid.size != 0) {
		/* Get the current SSID */
		memcpy(extra, priv->reg.ssid.body, priv->reg.ssid.size);

		/* If none, we may want to get the one that was set */

		/* Push it out ! */
		dwrq->essid.length = priv->reg.ssid.size;
		dwrq->essid.flags = 1;	/* active */
	} else {
		dwrq->essid.length = 0;
		dwrq->essid.flags = 0;	/* ANY */
	}

	return 0;
}