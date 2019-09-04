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
struct r8192_priv {scalar_t__ ChannelPlan; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 scalar_t__ COUNTRY_CODE_GLOBAL_DOMAIN ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  rtl819x_set_channel_map (scalar_t__,struct r8192_priv*) ; 

__attribute__((used)) static short rtl8192_get_channel_map(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	if (priv->ChannelPlan > COUNTRY_CODE_GLOBAL_DOMAIN) {
		netdev_err(dev,
			   "rtl8180_init: Error channel plan! Set to default.\n");
		priv->ChannelPlan = 0;
	}
	RT_TRACE(COMP_INIT, "Channel plan is %d\n", priv->ChannelPlan);

	rtl819x_set_channel_map(priv->ChannelPlan, priv);
	return 0;
}