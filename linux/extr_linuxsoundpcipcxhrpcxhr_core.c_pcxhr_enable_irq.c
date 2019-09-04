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
struct pcxhr_mgr {int dummy; } ;

/* Variables and functions */
 unsigned int PCXHR_INPL (struct pcxhr_mgr*,int /*<<< orphan*/ ) ; 
 unsigned int PCXHR_IRQCS_ENABLE_PCIDB ; 
 unsigned int PCXHR_IRQCS_ENABLE_PCIIRQ ; 
 int /*<<< orphan*/  PCXHR_OUTPL (struct pcxhr_mgr*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  PCXHR_PLX_IRQCS ; 

__attribute__((used)) static void pcxhr_enable_irq(struct pcxhr_mgr *mgr, int enable)
{
	unsigned int reg = PCXHR_INPL(mgr, PCXHR_PLX_IRQCS);
	/* enable/disable interrupts */
	if (enable)
		reg |=  (PCXHR_IRQCS_ENABLE_PCIIRQ | PCXHR_IRQCS_ENABLE_PCIDB);
	else
		reg &= ~(PCXHR_IRQCS_ENABLE_PCIIRQ | PCXHR_IRQCS_ENABLE_PCIDB);
	PCXHR_OUTPL(mgr, PCXHR_PLX_IRQCS, reg);
}