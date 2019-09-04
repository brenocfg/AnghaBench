#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct icom_port {int port; TYPE_3__* global_reg; TYPE_2__* adapter; } ;
struct TYPE_11__ {unsigned long processor_id; } ;
struct TYPE_10__ {unsigned long processor_id; int /*<<< orphan*/ * global_control_reg; } ;
struct TYPE_9__ {int /*<<< orphan*/  control_2; int /*<<< orphan*/  control; } ;
struct TYPE_8__ {TYPE_1__* pci_dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  icom_lock ; 
 unsigned long readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_5__* start_proc ; 
 TYPE_4__* stop_proc ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stop_processor(struct icom_port *icom_port)
{
	unsigned long temp;
	unsigned long flags;
	int port;

	spin_lock_irqsave(&icom_lock, flags);

	port = icom_port->port;
	if (port >= ARRAY_SIZE(stop_proc)) {
		dev_err(&icom_port->adapter->pci_dev->dev,
			"Invalid port assignment\n");
		goto unlock;
	}

	if (port == 0 || port == 1)
		stop_proc[port].global_control_reg = &icom_port->global_reg->control;
	else
		stop_proc[port].global_control_reg = &icom_port->global_reg->control_2;

	temp = readl(stop_proc[port].global_control_reg);
	temp = (temp & ~start_proc[port].processor_id) | stop_proc[port].processor_id;
	writel(temp, stop_proc[port].global_control_reg);

	/* write flush */
	readl(stop_proc[port].global_control_reg);

unlock:
	spin_unlock_irqrestore(&icom_lock, flags);
}