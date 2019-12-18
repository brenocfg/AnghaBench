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
struct fm801 {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 unsigned short fm801_ioread16 (struct fm801*,unsigned short) ; 
 int /*<<< orphan*/  fm801_iowrite16 (struct fm801*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_fm801_update_bits(struct fm801 *chip, unsigned short reg,
				 unsigned short mask, unsigned short value)
{
	int change;
	unsigned long flags;
	unsigned short old, new;

	spin_lock_irqsave(&chip->reg_lock, flags);
	old = fm801_ioread16(chip, reg);
	new = (old & ~mask) | value;
	change = old != new;
	if (change)
		fm801_iowrite16(chip, reg, new);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	return change;
}