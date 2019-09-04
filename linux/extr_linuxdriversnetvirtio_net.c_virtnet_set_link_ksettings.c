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
typedef  int /*<<< orphan*/  u32 ;
struct virtnet_info {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ethtool_validate_duplex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethtool_validate_speed (int /*<<< orphan*/ ) ; 
 struct virtnet_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  virtnet_validate_ethtool_cmd (struct ethtool_link_ksettings const*) ; 

__attribute__((used)) static int virtnet_set_link_ksettings(struct net_device *dev,
				      const struct ethtool_link_ksettings *cmd)
{
	struct virtnet_info *vi = netdev_priv(dev);
	u32 speed;

	speed = cmd->base.speed;
	/* don't allow custom speed and duplex */
	if (!ethtool_validate_speed(speed) ||
	    !ethtool_validate_duplex(cmd->base.duplex) ||
	    !virtnet_validate_ethtool_cmd(cmd))
		return -EINVAL;
	vi->speed = speed;
	vi->duplex = cmd->base.duplex;

	return 0;
}