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
struct sonicvibes {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  INDEX ; 
 int /*<<< orphan*/  SV_REG (struct sonicvibes*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_sonicvibes_out(struct sonicvibes * sonic,
			       unsigned char reg,
			       unsigned char value)
{
	unsigned long flags;

	spin_lock_irqsave(&sonic->reg_lock, flags);
	outb(reg, SV_REG(sonic, INDEX));
	udelay(10);
	outb(value, SV_REG(sonic, DATA));
	udelay(10);
	spin_unlock_irqrestore(&sonic->reg_lock, flags);
}