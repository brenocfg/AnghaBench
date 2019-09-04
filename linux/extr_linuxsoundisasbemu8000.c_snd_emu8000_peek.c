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
struct snd_emu8000 {unsigned int last_reg; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU8000_PTR (struct snd_emu8000*) ; 
 unsigned short inw (unsigned int) ; 
 int /*<<< orphan*/  outw (unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

unsigned short snd_emu8000_peek(struct snd_emu8000 *emu, unsigned int port, unsigned int reg)
{
	unsigned short res;
	unsigned long flags;
	spin_lock_irqsave(&emu->reg_lock, flags);
	if (reg != emu->last_reg) {
		outw((unsigned short)reg, EMU8000_PTR(emu)); /* Set register */
		emu->last_reg = reg;
	}
	res = inw(port);	/* Read data */
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	return res;
}