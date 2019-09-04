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
 int /*<<< orphan*/  NETCP_DRIVER_NAME ; 
 int /*<<< orphan*/  NETCP_DRIVER_VERSION ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void keystone_get_drvinfo(struct net_device *ndev,
				 struct ethtool_drvinfo *info)
{
	strncpy(info->driver, NETCP_DRIVER_NAME, sizeof(info->driver));
	strncpy(info->version, NETCP_DRIVER_VERSION, sizeof(info->version));
}