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
struct snd_opl3sa2 {scalar_t__ port; } ;

/* Variables and functions */
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

__attribute__((used)) static unsigned char __snd_opl3sa2_read(struct snd_opl3sa2 *chip, unsigned char reg)
{
	unsigned char result;
#if 0
	outb(0x1d, port);	/* password */
	printk(KERN_DEBUG "read [0x%lx] = 0x%x\n", port, inb(port));
#endif
	outb(reg, chip->port);	/* register */
	result = inb(chip->port + 1);
#if 0
	printk(KERN_DEBUG "read [0x%lx] = 0x%x [0x%x]\n",
	       port, result, inb(port));
#endif
	return result;
}