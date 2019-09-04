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
struct TYPE_2__ {int rx_intsup; int tx_intsup; int /*<<< orphan*/  txqueue_timer; int /*<<< orphan*/  rxqueue_timer; } ;
struct velocity_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  mac_regs; int /*<<< orphan*/  int_mask; TYPE_1__ options; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int tx_coalesce_usecs; int rx_coalesce_usecs; int tx_max_coalesced_frames; int rx_max_coalesced_frames; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mac_clear_isr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_disable_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_enable_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_write_int_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct velocity_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_pending_timer_val (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setup_adaptive_interrupts (struct velocity_info*) ; 
 int /*<<< orphan*/  setup_queue_timers (struct velocity_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int velocity_set_coalesce(struct net_device *dev,
		struct ethtool_coalesce *ecmd)
{
	struct velocity_info *vptr = netdev_priv(dev);
	int max_us = 0x3f * 64;
	unsigned long flags;

	/* 6 bits of  */
	if (ecmd->tx_coalesce_usecs > max_us)
		return -EINVAL;
	if (ecmd->rx_coalesce_usecs > max_us)
		return -EINVAL;

	if (ecmd->tx_max_coalesced_frames > 0xff)
		return -EINVAL;
	if (ecmd->rx_max_coalesced_frames > 0xff)
		return -EINVAL;

	vptr->options.rx_intsup = ecmd->rx_max_coalesced_frames;
	vptr->options.tx_intsup = ecmd->tx_max_coalesced_frames;

	set_pending_timer_val(&vptr->options.rxqueue_timer,
			ecmd->rx_coalesce_usecs);
	set_pending_timer_val(&vptr->options.txqueue_timer,
			ecmd->tx_coalesce_usecs);

	/* Setup the interrupt suppression and queue timers */
	spin_lock_irqsave(&vptr->lock, flags);
	mac_disable_int(vptr->mac_regs);
	setup_adaptive_interrupts(vptr);
	setup_queue_timers(vptr);

	mac_write_int_mask(vptr->int_mask, vptr->mac_regs);
	mac_clear_isr(vptr->mac_regs);
	mac_enable_int(vptr->mac_regs);
	spin_unlock_irqrestore(&vptr->lock, flags);

	return 0;
}