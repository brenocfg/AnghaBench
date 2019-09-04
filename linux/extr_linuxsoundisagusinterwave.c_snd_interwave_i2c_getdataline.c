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
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_interwave_i2c_getdataline(struct snd_i2c_bus *bus, int ack)
{
	unsigned long port = bus->private_value;
	unsigned char res;

	if (ack)
		udelay(10);
	res = (inb(port) & 2) >> 1;
#if 0
	printk(KERN_DEBUG "i2c_getdataline - 0x%lx -> %i\n", port, res);
#endif
	return res;
}