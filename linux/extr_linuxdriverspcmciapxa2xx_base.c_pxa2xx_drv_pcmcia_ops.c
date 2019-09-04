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
struct pcmcia_low_level {int /*<<< orphan*/  set_timing; } ;

/* Variables and functions */
 int /*<<< orphan*/  pxa2xx_pcmcia_set_timing ; 

void pxa2xx_drv_pcmcia_ops(struct pcmcia_low_level *ops)
{
	/* Provide our PXA2xx specific timing routines. */
	ops->set_timing  = pxa2xx_pcmcia_set_timing;
#ifdef CONFIG_CPU_FREQ
	ops->frequency_change = pxa2xx_pcmcia_frequency_change;
#endif
}