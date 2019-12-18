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
struct es1968 {scalar_t__ io_port; scalar_t__ rmidi; } ;

/* Variables and functions */
 unsigned short ESM_HIRQ_DSIE ; 
 unsigned short ESM_HIRQ_HW_VOLUME ; 
 unsigned short ESM_HIRQ_MPU401 ; 
 scalar_t__ ESM_PORT_HOST_IRQ ; 
 int /*<<< orphan*/  outb (unsigned short,scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 

__attribute__((used)) static void snd_es1968_start_irq(struct es1968 *chip)
{
	unsigned short w;
	w = ESM_HIRQ_DSIE | ESM_HIRQ_HW_VOLUME;
	if (chip->rmidi)
		w |= ESM_HIRQ_MPU401;
	outb(w, chip->io_port + 0x1A);
	outw(w, chip->io_port + ESM_PORT_HOST_IRQ);
}