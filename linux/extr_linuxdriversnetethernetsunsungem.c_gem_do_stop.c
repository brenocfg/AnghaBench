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
struct gem {TYPE_1__* pdev; scalar_t__ reset_task_pending; int /*<<< orphan*/  link_timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  gem_clean_rings (struct gem*) ; 
 int /*<<< orphan*/  gem_disable_ints (struct gem*) ; 
 int /*<<< orphan*/  gem_netif_stop (struct gem*) ; 
 int /*<<< orphan*/  gem_put_cell (struct gem*) ; 
 int /*<<< orphan*/  gem_reset (struct gem*) ; 
 int /*<<< orphan*/  gem_stop_dma (struct gem*) ; 
 int /*<<< orphan*/  gem_stop_phy (struct gem*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct gem* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_1__*) ; 

__attribute__((used)) static void gem_do_stop(struct net_device *dev, int wol)
{
	struct gem *gp = netdev_priv(dev);

	/* Stop NAPI and stop tx queue */
	gem_netif_stop(gp);

	/* Make sure ints are disabled. We don't care about
	 * synchronizing as NAPI is disabled, thus a stray
	 * interrupt will do nothing bad (our irq handler
	 * just schedules NAPI)
	 */
	gem_disable_ints(gp);

	/* Stop the link timer */
	del_timer_sync(&gp->link_timer);

	/* We cannot cancel the reset task while holding the
	 * rtnl lock, we'd get an A->B / B->A deadlock stituation
	 * if we did. This is not an issue however as the reset
	 * task is synchronized vs. us (rtnl_lock) and will do
	 * nothing if the device is down or suspended. We do
	 * still clear reset_task_pending to avoid a spurrious
	 * reset later on in case we do resume before it gets
	 * scheduled.
	 */
	gp->reset_task_pending = 0;

	/* If we are going to sleep with WOL */
	gem_stop_dma(gp);
	msleep(10);
	if (!wol)
		gem_reset(gp);
	msleep(10);

	/* Get rid of rings */
	gem_clean_rings(gp);

	/* No irq needed anymore */
	free_irq(gp->pdev->irq, (void *) dev);

	/* Shut the PHY down eventually and setup WOL */
	gem_stop_phy(gp, wol);

	/* Make sure bus master is disabled */
	pci_disable_device(gp->pdev);

	/* Cell not needed neither if no WOL */
	if (!wol)
		gem_put_cell(gp);
}