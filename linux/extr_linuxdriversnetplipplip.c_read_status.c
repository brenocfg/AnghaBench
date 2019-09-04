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
struct parport {TYPE_2__* ops; } ;
struct net_local {TYPE_1__* pardev; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {unsigned char (* read_status ) (struct parport*) ;} ;
struct TYPE_3__ {struct parport* port; } ;

/* Variables and functions */
 scalar_t__ netdev_priv (struct net_device*) ; 
 unsigned char stub1 (struct parport*) ; 

__attribute__((used)) static inline unsigned char read_status (struct net_device *dev)
{
	struct parport *port =
	   ((struct net_local *)netdev_priv(dev))->pardev->port;

	return port->ops->read_status (port);
}