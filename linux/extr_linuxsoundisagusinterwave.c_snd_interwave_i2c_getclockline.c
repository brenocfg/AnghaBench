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
 int inb (unsigned long) ; 

__attribute__((used)) static int snd_interwave_i2c_getclockline(struct snd_i2c_bus *bus)
{
	unsigned long port = bus->private_value;
	unsigned char res;

	res = inb(port) & 1;
#if 0
	printk(KERN_DEBUG "i2c_getclockline - 0x%lx -> %i\n", port, res);
#endif
	return res;
}