#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct es1938 {int /*<<< orphan*/  mixer_lock; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIXERADDR ; 
 int /*<<< orphan*/  MIXERDATA ; 
 int /*<<< orphan*/  SLSB_REG (struct es1938*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned char,unsigned char,unsigned char) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_es1938_mixer_bits(struct es1938 *chip, unsigned char reg,
				 unsigned char mask, unsigned char val)
{
	unsigned long flags;
	unsigned char old, new, oval;
	spin_lock_irqsave(&chip->mixer_lock, flags);
	outb(reg, SLSB_REG(chip, MIXERADDR));
	old = inb(SLSB_REG(chip, MIXERDATA));
	oval = old & mask;
	if (val != oval) {
		new = (old & ~mask) | (val & mask);
		outb(new, SLSB_REG(chip, MIXERDATA));
		dev_dbg(chip->card->dev,
			"Mixer reg %02x was %02x, set to %02x\n",
			   reg, old, new);
	}
	spin_unlock_irqrestore(&chip->mixer_lock, flags);
	return oval;
}