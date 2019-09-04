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
struct velocity_info {int /*<<< orphan*/  flags; int /*<<< orphan*/  napi; int /*<<< orphan*/  mac_regs; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  VELOCITY_FLAGS_OPENED ; 
 int /*<<< orphan*/  VELOCITY_INIT_COLD ; 
 int /*<<< orphan*/  mac_enable_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct velocity_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  velocity_free_rings (struct velocity_info*) ; 
 int /*<<< orphan*/  velocity_give_many_rx_descs (struct velocity_info*) ; 
 int /*<<< orphan*/  velocity_init_registers (struct velocity_info*,int /*<<< orphan*/ ) ; 
 int velocity_init_rings (struct velocity_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  velocity_intr ; 
 int /*<<< orphan*/  velocity_set_power_state (struct velocity_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int velocity_open(struct net_device *dev)
{
	struct velocity_info *vptr = netdev_priv(dev);
	int ret;

	ret = velocity_init_rings(vptr, dev->mtu);
	if (ret < 0)
		goto out;

	/* Ensure chip is running */
	velocity_set_power_state(vptr, PCI_D0);

	velocity_init_registers(vptr, VELOCITY_INIT_COLD);

	ret = request_irq(dev->irq, velocity_intr, IRQF_SHARED,
			  dev->name, dev);
	if (ret < 0) {
		/* Power down the chip */
		velocity_set_power_state(vptr, PCI_D3hot);
		velocity_free_rings(vptr);
		goto out;
	}

	velocity_give_many_rx_descs(vptr);

	mac_enable_int(vptr->mac_regs);
	netif_start_queue(dev);
	napi_enable(&vptr->napi);
	vptr->flags |= VELOCITY_FLAGS_OPENED;
out:
	return ret;
}