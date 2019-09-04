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
struct TYPE_2__ {unsigned int evtchn; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,unsigned int) ; 
 TYPE_1__* info_for_irq (unsigned int) ; 
 unsigned int nr_irqs ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

unsigned int evtchn_from_irq(unsigned irq)
{
	if (unlikely(WARN(irq >= nr_irqs, "Invalid irq %d!\n", irq)))
		return 0;

	return info_for_irq(irq)->evtchn;
}