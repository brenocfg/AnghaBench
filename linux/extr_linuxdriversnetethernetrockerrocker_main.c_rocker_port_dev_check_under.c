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
struct rocker_port {struct rocker* rocker; } ;
struct rocker {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct rocker_port* netdev_priv (struct net_device const*) ; 
 int /*<<< orphan*/  rocker_port_dev_check (struct net_device const*) ; 

__attribute__((used)) static bool rocker_port_dev_check_under(const struct net_device *dev,
					struct rocker *rocker)
{
	struct rocker_port *rocker_port;

	if (!rocker_port_dev_check(dev))
		return false;

	rocker_port = netdev_priv(dev);
	if (rocker_port->rocker != rocker)
		return false;

	return true;
}