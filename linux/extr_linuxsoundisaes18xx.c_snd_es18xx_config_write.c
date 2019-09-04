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
struct snd_es18xx {scalar_t__ ctrl_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

__attribute__((used)) static void snd_es18xx_config_write(struct snd_es18xx *chip,
				    unsigned char reg, unsigned char data)
{
	/* No need for spinlocks, this function is used only in
	   otherwise protected init code */
	outb(reg, chip->ctrl_port);
	outb(data, chip->ctrl_port + 1);
#ifdef REG_DEBUG
	snd_printk(KERN_DEBUG "Config reg %02x set to %02x\n", reg, data);
#endif
}