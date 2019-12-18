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
struct snd_gus_card {int /*<<< orphan*/  reg_lock; scalar_t__ interwave; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRAM ; 
 int EAGAIN ; 
 int /*<<< orphan*/  GF1DATALOW ; 
 int /*<<< orphan*/  GF1REGSEL ; 
 int /*<<< orphan*/  GUSP (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNDRV_GF1_GB_MEMORY_CONTROL ; 
 int /*<<< orphan*/  SNDRV_GF1_GW_DRAM_IO16 ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outsb (int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  outsw (int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_gf1_dram_addr (struct snd_gus_card*,unsigned int) ; 
 int /*<<< orphan*/  snd_gf1_poke (struct snd_gus_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_gf1_write8 (struct snd_gus_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_gf1_pcm_poke_block(struct snd_gus_card *gus, unsigned char *buf,
				  unsigned int pos, unsigned int count,
				  int w16, int invert)
{
	unsigned int len;
	unsigned long flags;

	/*
	printk(KERN_DEBUG
	       "poke block; buf = 0x%x, pos = %i, count = %i, port = 0x%x\n",
	       (int)buf, pos, count, gus->gf1.port);
	*/
	while (count > 0) {
		len = count;
		if (len > 512)		/* limit, to allow IRQ */
			len = 512;
		count -= len;
		if (gus->interwave) {
			spin_lock_irqsave(&gus->reg_lock, flags);
			snd_gf1_write8(gus, SNDRV_GF1_GB_MEMORY_CONTROL, 0x01 | (invert ? 0x08 : 0x00));
			snd_gf1_dram_addr(gus, pos);
			if (w16) {
				outb(SNDRV_GF1_GW_DRAM_IO16, GUSP(gus, GF1REGSEL));
				outsw(GUSP(gus, GF1DATALOW), buf, len >> 1);
			} else {
				outsb(GUSP(gus, DRAM), buf, len);
			}
			spin_unlock_irqrestore(&gus->reg_lock, flags);
			buf += 512;
			pos += 512;
		} else {
			invert = invert ? 0x80 : 0x00;
			if (w16) {
				len >>= 1;
				while (len--) {
					snd_gf1_poke(gus, pos++, *buf++);
					snd_gf1_poke(gus, pos++, *buf++ ^ invert);
				}
			} else {
				while (len--)
					snd_gf1_poke(gus, pos++, *buf++ ^ invert);
			}
		}
		if (count > 0 && !in_interrupt()) {
			schedule_timeout_interruptible(1);
			if (signal_pending(current))
				return -EAGAIN;
		}
	}
	return 0;
}