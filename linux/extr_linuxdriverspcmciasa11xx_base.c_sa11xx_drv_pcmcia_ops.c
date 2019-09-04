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
struct pcmcia_low_level {int /*<<< orphan*/  show_timing; int /*<<< orphan*/  set_timing; scalar_t__ get_timing; } ;

/* Variables and functions */
 scalar_t__ sa1100_pcmcia_default_mecr_timing ; 
 int /*<<< orphan*/  sa1100_pcmcia_set_timing ; 
 int /*<<< orphan*/  sa1100_pcmcia_show_timing ; 

void sa11xx_drv_pcmcia_ops(struct pcmcia_low_level *ops)
{
	/*
	 * set default MECR calculation if the board specific
	 * code did not specify one...
	 */
	if (!ops->get_timing)
		ops->get_timing = sa1100_pcmcia_default_mecr_timing;

	/* Provide our SA11x0 specific timing routines. */
	ops->set_timing  = sa1100_pcmcia_set_timing;
	ops->show_timing = sa1100_pcmcia_show_timing;
#ifdef CONFIG_CPU_FREQ
	ops->frequency_change = sa1100_pcmcia_frequency_change;
#endif
}