#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ipw_dev {TYPE_1__* hardware; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {scalar_t__ hw_version; } ;

/* Variables and functions */
 scalar_t__ HW_VERSION_1 ; 
 int /*<<< orphan*/  ipwireless_handle_v1_interrupt (int,TYPE_1__*) ; 
 int /*<<< orphan*/  ipwireless_handle_v2_v3_interrupt (int,TYPE_1__*) ; 

irqreturn_t ipwireless_interrupt(int irq, void *dev_id)
{
	struct ipw_dev *ipw = dev_id;

	if (ipw->hardware->hw_version == HW_VERSION_1)
		return ipwireless_handle_v1_interrupt(irq, ipw->hardware);
	else
		return ipwireless_handle_v2_v3_interrupt(irq, ipw->hardware);
}