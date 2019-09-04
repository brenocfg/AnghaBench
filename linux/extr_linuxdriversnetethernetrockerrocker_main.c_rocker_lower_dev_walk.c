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
struct rocker_walk_data {int /*<<< orphan*/  port; int /*<<< orphan*/  rocker; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 scalar_t__ rocker_port_dev_check_under (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rocker_lower_dev_walk(struct net_device *lower_dev, void *_data)
{
	struct rocker_walk_data *data = _data;
	int ret = 0;

	if (rocker_port_dev_check_under(lower_dev, data->rocker)) {
		data->port = netdev_priv(lower_dev);
		ret = 1;
	}

	return ret;
}