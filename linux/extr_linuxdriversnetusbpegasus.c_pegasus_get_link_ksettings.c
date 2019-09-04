#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ethtool_link_ksettings {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mii; } ;
typedef  TYPE_1__ pegasus_t ;

/* Variables and functions */
 int /*<<< orphan*/  mii_ethtool_get_link_ksettings (int /*<<< orphan*/ *,struct ethtool_link_ksettings*) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
pegasus_get_link_ksettings(struct net_device *dev,
			   struct ethtool_link_ksettings *ecmd)
{
	pegasus_t *pegasus;

	pegasus = netdev_priv(dev);
	mii_ethtool_get_link_ksettings(&pegasus->mii, ecmd);
	return 0;
}