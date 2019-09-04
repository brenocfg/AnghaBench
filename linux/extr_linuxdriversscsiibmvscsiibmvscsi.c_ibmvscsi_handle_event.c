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
struct ibmvscsi_host_data {int /*<<< orphan*/  srp_task; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_vio_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vio_disable_interrupts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ibmvscsi_handle_event(int irq, void *dev_instance)
{
	struct ibmvscsi_host_data *hostdata =
	    (struct ibmvscsi_host_data *)dev_instance;
	vio_disable_interrupts(to_vio_dev(hostdata->dev));
	tasklet_schedule(&hostdata->srp_task);
	return IRQ_HANDLED;
}