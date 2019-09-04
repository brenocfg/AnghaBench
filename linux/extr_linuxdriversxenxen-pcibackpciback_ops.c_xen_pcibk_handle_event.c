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
struct xen_pcibk_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  xen_pcibk_test_and_schedule_op (struct xen_pcibk_device*) ; 

irqreturn_t xen_pcibk_handle_event(int irq, void *dev_id)
{
	struct xen_pcibk_device *pdev = dev_id;

	xen_pcibk_test_and_schedule_op(pdev);

	return IRQ_HANDLED;
}