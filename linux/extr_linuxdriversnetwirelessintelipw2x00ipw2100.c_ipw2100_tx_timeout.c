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
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {int /*<<< orphan*/  name; TYPE_1__ stats; } ;
struct ipw2100_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*,int /*<<< orphan*/ ) ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_reset (struct ipw2100_priv*) ; 

__attribute__((used)) static void ipw2100_tx_timeout(struct net_device *dev)
{
	struct ipw2100_priv *priv = libipw_priv(dev);

	dev->stats.tx_errors++;

#ifdef CONFIG_IPW2100_MONITOR
	if (priv->ieee->iw_mode == IW_MODE_MONITOR)
		return;
#endif

	IPW_DEBUG_INFO("%s: TX timed out.  Scheduling firmware restart.\n",
		       dev->name);
	schedule_reset(priv);
}