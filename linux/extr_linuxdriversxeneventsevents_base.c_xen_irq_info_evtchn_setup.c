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
struct irq_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQT_EVTCHN ; 
 struct irq_info* info_for_irq (unsigned int) ; 
 int xen_irq_info_common_setup (struct irq_info*,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xen_irq_info_evtchn_setup(unsigned irq,
				     unsigned evtchn)
{
	struct irq_info *info = info_for_irq(irq);

	return xen_irq_info_common_setup(info, irq, IRQT_EVTCHN, evtchn, 0);
}