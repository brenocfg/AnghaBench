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
struct es1938 {int /*<<< orphan*/  reg_lock; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned char ESS_CMD_READREG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned char,unsigned char,unsigned char) ; 
 unsigned char snd_es1938_get_byte (struct es1938*) ; 
 int /*<<< orphan*/  snd_es1938_write_cmd (struct es1938*,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_es1938_bits(struct es1938 *chip, unsigned char reg, unsigned char mask,
			   unsigned char val)
{
	unsigned long flags;
	unsigned char old, new, oval;
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_es1938_write_cmd(chip, ESS_CMD_READREG);
	snd_es1938_write_cmd(chip, reg);
	old = snd_es1938_get_byte(chip);
	oval = old & mask;
	if (val != oval) {
		snd_es1938_write_cmd(chip, reg);
		new = (old & ~mask) | (val & mask);
		snd_es1938_write_cmd(chip, new);
		dev_dbg(chip->card->dev, "Reg %02x was %02x, set to %02x\n",
			   reg, old, new);
	}
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	return oval;
}