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
struct net_device {int dummy; } ;
struct TYPE_2__ {int speed; int /*<<< orphan*/  port; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  PORT_NONE ; 
 int /*<<< orphan*/  advertising ; 
 int /*<<< orphan*/  ethtool_link_ksettings_zero_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supported ; 

__attribute__((used)) static int fjes_get_link_ksettings(struct net_device *netdev,
				   struct ethtool_link_ksettings *ecmd)
{
	ethtool_link_ksettings_zero_link_mode(ecmd, supported);
	ethtool_link_ksettings_zero_link_mode(ecmd, advertising);
	ecmd->base.duplex = DUPLEX_FULL;
	ecmd->base.autoneg = AUTONEG_DISABLE;
	ecmd->base.port = PORT_NONE;
	ecmd->base.speed = 20000;	/* 20Gb/s */

	return 0;
}