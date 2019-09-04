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
struct snd_i2c_bus {unsigned long private_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb (int,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_interwave_i2c_setlines(struct snd_i2c_bus *bus, int ctrl, int data)
{
	unsigned long port = bus->private_value;

#if 0
	printk(KERN_DEBUG "i2c_setlines - 0x%lx <- %i,%i\n", port, ctrl, data);
#endif
	outb((data << 1) | ctrl, port);
	udelay(10);
}