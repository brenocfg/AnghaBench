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
struct r8192_priv {int /*<<< orphan*/  chan; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CH ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_phy_FinishSwChnlNow (struct net_device*,int /*<<< orphan*/ ) ; 

void rtl8192_SwChnl_WorkItem(struct net_device *dev)
{

	struct r8192_priv *priv = ieee80211_priv(dev);

	RT_TRACE(COMP_CH, "==> SwChnlCallback819xUsbWorkItem(), chan:%d\n",
		 priv->chan);


	rtl8192_phy_FinishSwChnlNow(dev, priv->chan);

	RT_TRACE(COMP_CH, "<== SwChnlCallback819xUsbWorkItem()\n");
}