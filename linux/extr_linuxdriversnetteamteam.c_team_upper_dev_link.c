#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct team_port {TYPE_2__* dev; } ;
struct team {int /*<<< orphan*/  dev; TYPE_1__* mode; } ;
struct netlink_ext_ack {int dummy; } ;
struct netdev_lag_upper_info {int /*<<< orphan*/  hash_type; int /*<<< orphan*/  tx_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  priv_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  lag_tx_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_TEAM_PORT ; 
 int /*<<< orphan*/  NETDEV_LAG_HASH_UNKNOWN ; 
 int netdev_master_upper_dev_link (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct netdev_lag_upper_info*,struct netlink_ext_ack*) ; 

__attribute__((used)) static int team_upper_dev_link(struct team *team, struct team_port *port,
			       struct netlink_ext_ack *extack)
{
	struct netdev_lag_upper_info lag_upper_info;
	int err;

	lag_upper_info.tx_type = team->mode->lag_tx_type;
	lag_upper_info.hash_type = NETDEV_LAG_HASH_UNKNOWN;
	err = netdev_master_upper_dev_link(port->dev, team->dev, NULL,
					   &lag_upper_info, extack);
	if (err)
		return err;
	port->dev->priv_flags |= IFF_TEAM_PORT;
	return 0;
}