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
typedef  int u16 ;
struct rtllib_network {int beacon_interval; } ;
struct r8192_priv {TYPE_1__* rtllib; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct rtllib_network current_network; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATIMWND ; 
 int /*<<< orphan*/  BCN_DMATIME ; 
 int /*<<< orphan*/  BCN_DRV_EARLY_INT ; 
 int /*<<< orphan*/  BCN_ERR_THRESH ; 
 int /*<<< orphan*/  BCN_INTERVAL ; 
 int /*<<< orphan*/  BCN_TCFG ; 
 int BCN_TCFG_CW_SHIFT ; 
 int BCN_TCFG_IFS ; 
 int /*<<< orphan*/  rtl92e_irq_disable (struct net_device*) ; 
 int /*<<< orphan*/  rtl92e_irq_enable (struct net_device*) ; 
 int /*<<< orphan*/  rtl92e_writeb (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl92e_writew (struct net_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rtllib_priv (struct net_device*) ; 

void rtl92e_start_beacon(struct net_device *dev)
{
	struct r8192_priv *priv = (struct r8192_priv *)rtllib_priv(dev);
	struct rtllib_network *net = &priv->rtllib->current_network;
	u16 BcnTimeCfg = 0;
	u16 BcnCW = 6;
	u16 BcnIFS = 0xf;

	rtl92e_irq_disable(dev);

	rtl92e_writew(dev, ATIMWND, 2);

	rtl92e_writew(dev, BCN_INTERVAL, net->beacon_interval);
	rtl92e_writew(dev, BCN_DRV_EARLY_INT, 10);
	rtl92e_writew(dev, BCN_DMATIME, 256);

	rtl92e_writeb(dev, BCN_ERR_THRESH, 100);

	BcnTimeCfg |= BcnCW<<BCN_TCFG_CW_SHIFT;
	BcnTimeCfg |= BcnIFS<<BCN_TCFG_IFS;
	rtl92e_writew(dev, BCN_TCFG, BcnTimeCfg);
	rtl92e_irq_enable(dev);
}