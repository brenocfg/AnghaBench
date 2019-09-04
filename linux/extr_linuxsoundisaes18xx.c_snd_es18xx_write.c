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
struct snd_es18xx {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int snd_es18xx_dsp_command (struct snd_es18xx*,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_es18xx_write(struct snd_es18xx *chip,
			    unsigned char reg, unsigned char data)
{
	unsigned long flags;
	int ret;
	
        spin_lock_irqsave(&chip->reg_lock, flags);
	ret = snd_es18xx_dsp_command(chip, reg);
	if (ret < 0)
		goto end;
        ret = snd_es18xx_dsp_command(chip, data);
 end:
        spin_unlock_irqrestore(&chip->reg_lock, flags);
#ifdef REG_DEBUG
	snd_printk(KERN_DEBUG "Reg %02x set to %02x\n", reg, data);
#endif
	return ret;
}