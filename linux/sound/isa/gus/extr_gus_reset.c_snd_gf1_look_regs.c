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
struct snd_gus_card {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUSP (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQSTAT ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_gf1_look8 (struct snd_gus_card*,int) ; 
 int /*<<< orphan*/  snd_gf1_read8 (struct snd_gus_card*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_gf1_look_regs(struct snd_gus_card * gus)
{
	unsigned long flags;

	spin_lock_irqsave(&gus->reg_lock, flags);
	snd_gf1_look8(gus, 0x41);	/* DRAM DMA Control Register */
	snd_gf1_look8(gus, 0x49);	/* Sampling Control Register */
	inb(GUSP(gus, IRQSTAT));
	snd_gf1_read8(gus, 0x0f);	/* IRQ Source Register */
	spin_unlock_irqrestore(&gus->reg_lock, flags);
}