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
struct ethtool_drvinfo {int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 char* vlan_fullname ; 
 char* vlan_version ; 

__attribute__((used)) static void vlan_ethtool_get_drvinfo(struct net_device *dev,
				     struct ethtool_drvinfo *info)
{
	strlcpy(info->driver, vlan_fullname, sizeof(info->driver));
	strlcpy(info->version, vlan_version, sizeof(info->version));
	strlcpy(info->fw_version, "N/A", sizeof(info->fw_version));
}