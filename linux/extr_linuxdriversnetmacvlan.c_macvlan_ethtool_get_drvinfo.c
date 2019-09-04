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
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void macvlan_ethtool_get_drvinfo(struct net_device *dev,
					struct ethtool_drvinfo *drvinfo)
{
	strlcpy(drvinfo->driver, "macvlan", sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, "0.1", sizeof(drvinfo->version));
}