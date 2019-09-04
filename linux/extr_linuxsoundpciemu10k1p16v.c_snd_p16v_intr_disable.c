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
struct snd_emu10k1 {int /*<<< orphan*/  emu_lock; scalar_t__ port; } ;

/* Variables and functions */
 scalar_t__ INTE2 ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_p16v_intr_disable(struct snd_emu10k1 *emu, unsigned int intrenb)
{
	unsigned long flags;
	unsigned int disable;

	spin_lock_irqsave(&emu->emu_lock, flags);
	disable = inl(emu->port + INTE2) & (~intrenb);
	outl(disable, emu->port + INTE2);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
}