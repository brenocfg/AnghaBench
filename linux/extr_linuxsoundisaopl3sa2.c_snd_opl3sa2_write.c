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
struct snd_opl3sa2 {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __snd_opl3sa2_write (struct snd_opl3sa2*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_opl3sa2_write(struct snd_opl3sa2 *chip, unsigned char reg, unsigned char value)
{
	unsigned long flags;
	spin_lock_irqsave(&chip->reg_lock, flags);
	__snd_opl3sa2_write(chip, reg, value);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
}