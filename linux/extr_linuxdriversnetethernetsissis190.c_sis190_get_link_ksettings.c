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
struct sis190_private {int /*<<< orphan*/  mii_if; } ;
struct net_device {int dummy; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mii_ethtool_get_link_ksettings (int /*<<< orphan*/ *,struct ethtool_link_ksettings*) ; 
 struct sis190_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int sis190_get_link_ksettings(struct net_device *dev,
				     struct ethtool_link_ksettings *cmd)
{
	struct sis190_private *tp = netdev_priv(dev);

	mii_ethtool_get_link_ksettings(&tp->mii_if, cmd);

	return 0;
}