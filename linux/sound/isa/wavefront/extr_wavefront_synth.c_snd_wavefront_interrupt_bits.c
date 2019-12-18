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

/* Variables and functions */
 int /*<<< orphan*/  snd_printk (char*,int) ; 

__attribute__((used)) static int
snd_wavefront_interrupt_bits (int irq)

{
	int bits;

	switch (irq) {
	case 9:
		bits = 0x00;
		break;
	case 5:
		bits = 0x08;
		break;
	case 12:
		bits = 0x10;
		break;
	case 15:
		bits = 0x18;
		break;
	
	default:
		snd_printk ("invalid IRQ %d\n", irq);
		bits = -1;
	}

	return bits;
}