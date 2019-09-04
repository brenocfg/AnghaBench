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
struct TYPE_3__ {int value; scalar_t__ disabled; } ;
union iwreq_data {TYPE_1__ rts; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int rts; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; int /*<<< orphan*/  need_commit; TYPE_2__ reg; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ SLP_SLEEP ; 
 int /*<<< orphan*/  SME_RTS ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_set_rts(struct net_device *dev, struct iw_request_info *info,
			   union iwreq_data *vwrq, char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);
	int rthr = vwrq->rts.value;

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;

	/* for SLEEP MODE */
	if (vwrq->rts.disabled)
		rthr = 2347;
	if ((rthr < 0) || (rthr > 2347))
		return -EINVAL;

	priv->reg.rts = rthr;
	priv->need_commit |= SME_RTS;

	return -EINPROGRESS;	/* Call commit handler */
}