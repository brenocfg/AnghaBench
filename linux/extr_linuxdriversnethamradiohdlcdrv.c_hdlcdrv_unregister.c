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
struct hdlcdrv_state {scalar_t__ magic; TYPE_1__* ops; scalar_t__ opened; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ HDLCDRV_MAGIC ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct hdlcdrv_state* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

void hdlcdrv_unregister(struct net_device *dev) 
{
	struct hdlcdrv_state *s = netdev_priv(dev);

	BUG_ON(s->magic != HDLCDRV_MAGIC);

	if (s->opened && s->ops->close)
		s->ops->close(dev);
	unregister_netdev(dev);
	
	free_netdev(dev);
}