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
struct irq_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* bind_to_cpu ) (struct irq_info*,unsigned int) ;} ;

/* Variables and functions */
 TYPE_1__* evtchn_ops ; 
 int /*<<< orphan*/  stub1 (struct irq_info*,unsigned int) ; 

__attribute__((used)) static inline void xen_evtchn_port_bind_to_cpu(struct irq_info *info,
					       unsigned cpu)
{
	evtchn_ops->bind_to_cpu(info, cpu);
}