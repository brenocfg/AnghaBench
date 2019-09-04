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
struct es1938 {TYPE_1__* card; int /*<<< orphan*/  reg_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned char ESS_CMD_READREG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned char,unsigned char) ; 
 unsigned char snd_es1938_get_byte (struct es1938*) ; 
 int /*<<< orphan*/  snd_es1938_write_cmd (struct es1938*,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned char snd_es1938_read(struct es1938 *chip, unsigned char reg)
{
	unsigned char val;
	unsigned long flags;
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_es1938_write_cmd(chip, ESS_CMD_READREG);
	snd_es1938_write_cmd(chip, reg);
	val = snd_es1938_get_byte(chip);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	dev_dbg(chip->card->dev, "Reg %02x now is %02x\n", reg, val);
	return val;
}