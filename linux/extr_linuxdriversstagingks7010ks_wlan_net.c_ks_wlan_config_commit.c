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
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct net_device {int dummy; } ;
struct ks_wlan_private {scalar_t__ need_commit; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ks_wlan_setup_parameter (struct ks_wlan_private*,scalar_t__) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_config_commit(struct net_device *dev,
				 struct iw_request_info *info,
				 union iwreq_data *zwrq,
				 char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);

	if (!priv->need_commit)
		return 0;

	ks_wlan_setup_parameter(priv, priv->need_commit);
	priv->need_commit = 0;
	return 0;
}