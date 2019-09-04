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
struct rtllib_device {int /*<<< orphan*/  (* AllowAllDestAddrHandler ) (struct net_device*,int,int) ;} ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct rtllib_device* netdev_priv_rsl (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int,int) ; 

void rtllib_EnableNetMonitorMode(struct net_device *dev,
		bool bInitState)
{
	struct rtllib_device *ieee = netdev_priv_rsl(dev);

	netdev_info(dev, "========>Enter Monitor Mode\n");

	ieee->AllowAllDestAddrHandler(dev, true, !bInitState);
}