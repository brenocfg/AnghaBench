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
struct snd_es18xx {int /*<<< orphan*/  mixer_lock; scalar_t__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void snd_es18xx_mixer_write(struct snd_es18xx *chip,
			    unsigned char reg, unsigned char data)
{
	unsigned long flags;
        spin_lock_irqsave(&chip->mixer_lock, flags);
        outb(reg, chip->port + 0x04);
        outb(data, chip->port + 0x05);
        spin_unlock_irqrestore(&chip->mixer_lock, flags);
#ifdef REG_DEBUG
	snd_printk(KERN_DEBUG "Mixer reg %02x set to %02x\n", reg, data);
#endif
}