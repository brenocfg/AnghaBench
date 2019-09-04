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
struct irq_info {scalar_t__ evtchn; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_evtchn_to_irq (scalar_t__,int) ; 

__attribute__((used)) static void xen_irq_info_cleanup(struct irq_info *info)
{
	set_evtchn_to_irq(info->evtchn, -1);
	info->evtchn = 0;
}