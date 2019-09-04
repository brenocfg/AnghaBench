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
struct irq_info {int refcnt; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int get_evtchn_to_irq (unsigned int) ; 
 struct irq_info* irq_get_handler_data (int) ; 

int evtchn_make_refcounted(unsigned int evtchn)
{
	int irq = get_evtchn_to_irq(evtchn);
	struct irq_info *info;

	if (irq == -1)
		return -ENOENT;

	info = irq_get_handler_data(irq);

	if (!info)
		return -ENOENT;

	WARN_ON(info->refcnt != -1);

	info->refcnt = 1;

	return 0;
}