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
struct TYPE_2__ {scalar_t__ length; } ;
union iwreq_data {TYPE_1__ data; } ;
struct net_device {int dummy; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; int /*<<< orphan*/  nick; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ SLP_SLEEP ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ks_wlan_get_nick(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *dwrq, char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;

	/* for SLEEP MODE */
	strncpy(extra, priv->nick, 16);
	extra[16] = '\0';
	dwrq->data.length = strlen(extra) + 1;

	return 0;
}