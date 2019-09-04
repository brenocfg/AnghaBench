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
struct rproc {int /*<<< orphan*/  bootaddr; struct keystone_rproc* priv; } ;
struct keystone_rproc {int /*<<< orphan*/  workqueue; int /*<<< orphan*/  irq_ring; int /*<<< orphan*/  irq_fault; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct keystone_rproc*) ; 
 int /*<<< orphan*/  handle_event ; 
 int keystone_rproc_dsp_boot (struct keystone_rproc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keystone_rproc_exception_interrupt ; 
 int /*<<< orphan*/  keystone_rproc_vring_interrupt ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct keystone_rproc*) ; 

__attribute__((used)) static int keystone_rproc_start(struct rproc *rproc)
{
	struct keystone_rproc *ksproc = rproc->priv;
	int ret;

	INIT_WORK(&ksproc->workqueue, handle_event);

	ret = request_irq(ksproc->irq_ring, keystone_rproc_vring_interrupt, 0,
			  dev_name(ksproc->dev), ksproc);
	if (ret) {
		dev_err(ksproc->dev, "failed to enable vring interrupt, ret = %d\n",
			ret);
		goto out;
	}

	ret = request_irq(ksproc->irq_fault, keystone_rproc_exception_interrupt,
			  0, dev_name(ksproc->dev), ksproc);
	if (ret) {
		dev_err(ksproc->dev, "failed to enable exception interrupt, ret = %d\n",
			ret);
		goto free_vring_irq;
	}

	ret = keystone_rproc_dsp_boot(ksproc, rproc->bootaddr);
	if (ret)
		goto free_exc_irq;

	return 0;

free_exc_irq:
	free_irq(ksproc->irq_fault, ksproc);
free_vring_irq:
	free_irq(ksproc->irq_ring, ksproc);
	flush_work(&ksproc->workqueue);
out:
	return ret;
}