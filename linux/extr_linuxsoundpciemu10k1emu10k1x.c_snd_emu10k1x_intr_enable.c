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
struct emu10k1x {int /*<<< orphan*/  emu_lock; scalar_t__ port; } ;

/* Variables and functions */
 scalar_t__ INTE ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_emu10k1x_intr_enable(struct emu10k1x *emu, unsigned int intrenb)
{
	unsigned long flags;
	unsigned int intr_enable;

	spin_lock_irqsave(&emu->emu_lock, flags);
	intr_enable = inl(emu->port + INTE) | intrenb;
	outl(intr_enable, emu->port + INTE);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
}