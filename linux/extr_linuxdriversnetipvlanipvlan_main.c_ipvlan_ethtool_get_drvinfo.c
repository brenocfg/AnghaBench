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
struct ethtool_drvinfo {int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPVLAN_DRV ; 
 int /*<<< orphan*/  IPV_DRV_VER ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ipvlan_ethtool_get_drvinfo(struct net_device *dev,
				       struct ethtool_drvinfo *drvinfo)
{
	strlcpy(drvinfo->driver, IPVLAN_DRV, sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, IPV_DRV_VER, sizeof(drvinfo->version));
}