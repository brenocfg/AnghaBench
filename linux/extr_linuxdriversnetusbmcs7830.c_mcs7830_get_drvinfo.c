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
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbnet_get_drvinfo (struct net_device*,struct ethtool_drvinfo*) ; 

__attribute__((used)) static void mcs7830_get_drvinfo(struct net_device *net, struct ethtool_drvinfo *drvinfo)
{
	usbnet_get_drvinfo(net, drvinfo);
}