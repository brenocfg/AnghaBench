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
struct vfio_platform_irq {int /*<<< orphan*/  hwirq; int /*<<< orphan*/  masked; struct eventfd_ctx* trigger; int /*<<< orphan*/  name; } ;
struct vfio_platform_device {int /*<<< orphan*/  name; struct vfio_platform_irq* irqs; } ;
struct eventfd_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQ_NOAUTOEN ; 
 scalar_t__ IS_ERR (struct eventfd_ctx*) ; 
 int PTR_ERR (struct eventfd_ctx*) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct eventfd_ctx* eventfd_ctx_fdget (int) ; 
 int /*<<< orphan*/  eventfd_ctx_put (struct eventfd_ctx*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct vfio_platform_irq*) ; 
 int /*<<< orphan*/  irq_clear_status_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_status_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vfio_platform_irq*) ; 

__attribute__((used)) static int vfio_set_trigger(struct vfio_platform_device *vdev, int index,
			    int fd, irq_handler_t handler)
{
	struct vfio_platform_irq *irq = &vdev->irqs[index];
	struct eventfd_ctx *trigger;
	int ret;

	if (irq->trigger) {
		irq_clear_status_flags(irq->hwirq, IRQ_NOAUTOEN);
		free_irq(irq->hwirq, irq);
		kfree(irq->name);
		eventfd_ctx_put(irq->trigger);
		irq->trigger = NULL;
	}

	if (fd < 0) /* Disable only */
		return 0;

	irq->name = kasprintf(GFP_KERNEL, "vfio-irq[%d](%s)",
						irq->hwirq, vdev->name);
	if (!irq->name)
		return -ENOMEM;

	trigger = eventfd_ctx_fdget(fd);
	if (IS_ERR(trigger)) {
		kfree(irq->name);
		return PTR_ERR(trigger);
	}

	irq->trigger = trigger;

	irq_set_status_flags(irq->hwirq, IRQ_NOAUTOEN);
	ret = request_irq(irq->hwirq, handler, 0, irq->name, irq);
	if (ret) {
		kfree(irq->name);
		eventfd_ctx_put(trigger);
		irq->trigger = NULL;
		return ret;
	}

	if (!irq->masked)
		enable_irq(irq->hwirq);

	return 0;
}