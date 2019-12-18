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
 int /*<<< orphan*/  pcxhr_enable_irq (struct pcxhr_mgr*,int) ; 

void pcxhr_enable_dsp(struct pcxhr_mgr *mgr)
{
	/* enable interrupts */
	pcxhr_enable_irq(mgr, 1);
}