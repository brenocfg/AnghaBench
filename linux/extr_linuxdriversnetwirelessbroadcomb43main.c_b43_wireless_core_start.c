#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct b43_wldev {TYPE_1__* wl; int /*<<< orphan*/  irq_mask; TYPE_3__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_MMIO_GEN_IRQ_MASK ; 
 scalar_t__ B43_STAT_INITIALIZED ; 
 int /*<<< orphan*/  B43_STAT_STARTED ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 scalar_t__ b43_bus_host_is_sdio (TYPE_3__*) ; 
 int /*<<< orphan*/  b43_interrupt_handler ; 
 int /*<<< orphan*/  b43_interrupt_thread_handler ; 
 int /*<<< orphan*/  b43_leds_init (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_mac_enable (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_periodic_tasks_setup (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_sdio_interrupt_handler ; 
 int b43_sdio_request_irq (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_set_status (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 scalar_t__ b43_status (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_write32 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  b43err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  drain_txstatus_queue (struct b43_wldev*) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct b43_wldev*) ; 

__attribute__((used)) static int b43_wireless_core_start(struct b43_wldev *dev)
{
	int err;

	B43_WARN_ON(b43_status(dev) != B43_STAT_INITIALIZED);

	drain_txstatus_queue(dev);
	if (b43_bus_host_is_sdio(dev->dev)) {
		err = b43_sdio_request_irq(dev, b43_sdio_interrupt_handler);
		if (err) {
			b43err(dev->wl, "Cannot request SDIO IRQ\n");
			goto out;
		}
	} else {
		err = request_threaded_irq(dev->dev->irq, b43_interrupt_handler,
					   b43_interrupt_thread_handler,
					   IRQF_SHARED, KBUILD_MODNAME, dev);
		if (err) {
			b43err(dev->wl, "Cannot request IRQ-%d\n",
			       dev->dev->irq);
			goto out;
		}
	}

	/* We are ready to run. */
	ieee80211_wake_queues(dev->wl->hw);
	b43_set_status(dev, B43_STAT_STARTED);

	/* Start data flow (TX/RX). */
	b43_mac_enable(dev);
	b43_write32(dev, B43_MMIO_GEN_IRQ_MASK, dev->irq_mask);

	/* Start maintenance work */
	b43_periodic_tasks_setup(dev);

	b43_leds_init(dev);

	b43dbg(dev->wl, "Wireless interface started\n");
out:
	return err;
}