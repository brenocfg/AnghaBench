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
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int speed; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;
struct cbs_sched_data {int /*<<< orphan*/  port_rate; } ;

/* Variables and functions */
 int BYTES_PER_KBIT ; 
 int SPEED_10 ; 
 int SPEED_UNKNOWN ; 
 int __ethtool_get_link_ksettings (struct net_device*,struct ethtool_link_ksettings*) ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int /*<<< orphan*/ ,long long,int) ; 

__attribute__((used)) static void cbs_set_port_rate(struct net_device *dev, struct cbs_sched_data *q)
{
	struct ethtool_link_ksettings ecmd;
	int speed = SPEED_10;
	int port_rate;
	int err;

	err = __ethtool_get_link_ksettings(dev, &ecmd);
	if (err < 0)
		goto skip;

	if (ecmd.base.speed && ecmd.base.speed != SPEED_UNKNOWN)
		speed = ecmd.base.speed;

skip:
	port_rate = speed * 1000 * BYTES_PER_KBIT;

	atomic64_set(&q->port_rate, port_rate);
	netdev_dbg(dev, "cbs: set %s's port_rate to: %lld, linkspeed: %d\n",
		   dev->name, (long long)atomic64_read(&q->port_rate),
		   ecmd.base.speed);
}