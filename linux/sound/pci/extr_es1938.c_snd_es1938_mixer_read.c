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
struct es1938 {TYPE_1__* card; int /*<<< orphan*/  mixer_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIXERADDR ; 
 int /*<<< orphan*/  MIXERDATA ; 
 int /*<<< orphan*/  SLSB_REG (struct es1938*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned char,int) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_es1938_mixer_read(struct es1938 *chip, unsigned char reg)
{
	int data;
	unsigned long flags;
	spin_lock_irqsave(&chip->mixer_lock, flags);
	outb(reg, SLSB_REG(chip, MIXERADDR));
	data = inb(SLSB_REG(chip, MIXERDATA));
	spin_unlock_irqrestore(&chip->mixer_lock, flags);
	dev_dbg(chip->card->dev, "Mixer reg %02x now is %02x\n", reg, data);
	return data;
}