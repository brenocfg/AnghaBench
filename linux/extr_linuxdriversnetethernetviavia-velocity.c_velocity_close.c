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
struct velocity_info {int flags; int /*<<< orphan*/  napi; } ;
struct net_device {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int VELOCITY_FLAGS_OPENED ; 
 int VELOCITY_FLAGS_WOL_ENABLED ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct velocity_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  velocity_free_rings (struct velocity_info*) ; 
 int /*<<< orphan*/  velocity_get_ip (struct velocity_info*) ; 
 int /*<<< orphan*/  velocity_shutdown (struct velocity_info*) ; 

__attribute__((used)) static int velocity_close(struct net_device *dev)
{
	struct velocity_info *vptr = netdev_priv(dev);

	napi_disable(&vptr->napi);
	netif_stop_queue(dev);
	velocity_shutdown(vptr);

	if (vptr->flags & VELOCITY_FLAGS_WOL_ENABLED)
		velocity_get_ip(vptr);

	free_irq(dev->irq, dev);

	velocity_free_rings(vptr);

	vptr->flags &= (~VELOCITY_FLAGS_OPENED);
	return 0;
}