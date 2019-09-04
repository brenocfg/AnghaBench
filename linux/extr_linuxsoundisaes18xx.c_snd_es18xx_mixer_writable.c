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
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int snd_es18xx_mixer_writable(struct snd_es18xx *chip, unsigned char reg,
					    unsigned char mask)
{
	int old, expected, new;
	unsigned long flags;
        spin_lock_irqsave(&chip->mixer_lock, flags);
        outb(reg, chip->port + 0x04);
	old = inb(chip->port + 0x05);
	expected = old ^ mask;
	outb(expected, chip->port + 0x05);
	new = inb(chip->port + 0x05);
        spin_unlock_irqrestore(&chip->mixer_lock, flags);
#ifdef REG_DEBUG
	snd_printk(KERN_DEBUG "Mixer reg %02x was %02x, set to %02x, now is %02x\n",
		   reg, old, expected, new);
#endif
	return expected == new;
}