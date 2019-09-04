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
struct TYPE_2__ {int ipi; } ;
struct irq_info {TYPE_1__ u; } ;
typedef  enum ipi_vector { ____Placeholder_ipi_vector } ipi_vector ;

/* Variables and functions */
 int /*<<< orphan*/  IRQT_IPI ; 
 struct irq_info* info_for_irq (unsigned int) ; 
 int /*<<< orphan*/  ipi_to_irq ; 
 unsigned int* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int xen_irq_info_common_setup (struct irq_info*,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xen_irq_info_ipi_setup(unsigned cpu,
				  unsigned irq,
				  unsigned evtchn,
				  enum ipi_vector ipi)
{
	struct irq_info *info = info_for_irq(irq);

	info->u.ipi = ipi;

	per_cpu(ipi_to_irq, cpu)[ipi] = irq;

	return xen_irq_info_common_setup(info, irq, IRQT_IPI, evtchn, 0);
}