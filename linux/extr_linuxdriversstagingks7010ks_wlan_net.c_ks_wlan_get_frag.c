#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int value; int disabled; int fixed; } ;
union iwreq_data {TYPE_2__ frag; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int fragment; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; TYPE_1__ reg; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ SLP_SLEEP ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_get_frag(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *vwrq, char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;

	/* for SLEEP MODE */
	vwrq->frag.value = priv->reg.fragment;
	vwrq->frag.disabled = (vwrq->frag.value >= 2346);
	vwrq->frag.fixed = 1;

	return 0;
}