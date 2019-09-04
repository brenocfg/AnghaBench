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
struct TYPE_4__ {int value; scalar_t__ disabled; } ;
union iwreq_data {TYPE_2__ frag; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int fragment; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; int /*<<< orphan*/  need_commit; TYPE_1__ reg; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ SLP_SLEEP ; 
 int /*<<< orphan*/  SME_FRAG ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_set_frag(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *vwrq, char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);
	int fthr = vwrq->frag.value;

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;

	/* for SLEEP MODE */
	if (vwrq->frag.disabled)
		fthr = 2346;
	if ((fthr < 256) || (fthr > 2346))
		return -EINVAL;

	fthr &= ~0x1;	/* Get an even value - is it really needed ??? */
	priv->reg.fragment = fthr;
	priv->need_commit |= SME_FRAG;

	return -EINPROGRESS;	/* Call commit handler */
}