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
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ phy_type; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; int /*<<< orphan*/  need_commit; TYPE_1__ reg; } ;
struct iw_request_info {int dummy; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ D_11BG_COMPATIBLE_MODE ; 
 scalar_t__ D_11B_ONLY_MODE ; 
 scalar_t__ D_11G_ONLY_MODE ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ SLP_SLEEP ; 
 int /*<<< orphan*/  SME_MODE_SET ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_set_phy_type(struct net_device *dev,
				struct iw_request_info *info, __u32 *uwrq,
				char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;

	if (*uwrq != D_11B_ONLY_MODE &&
	    *uwrq != D_11G_ONLY_MODE &&
	    *uwrq != D_11BG_COMPATIBLE_MODE)
		return -EINVAL;

	/* for SLEEP MODE */
	priv->reg.phy_type = *uwrq;
	priv->need_commit |= SME_MODE_SET;
	return -EINPROGRESS;	/* Call commit handler */
}