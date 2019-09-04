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
struct TYPE_2__ {int port; } ;
struct snd_gus_card {TYPE_1__ gf1; } ;
struct snd_es1688 {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  mixer_lock; } ;

/* Variables and functions */
 int EIO ; 
 int ES1688P (struct snd_es1688*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT1 ; 
 int /*<<< orphan*/  SNDRV_GF1_GB_RESET ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  snd_es1688_mixer_write (struct snd_es1688*,int,int) ; 
 unsigned char snd_gf1_i_look8 (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_gf1_i_write8 (struct snd_gus_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_printdd (char*,int,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_gusextreme_detect(struct snd_gus_card *gus,
				 struct snd_es1688 *es1688)
{
	unsigned long flags;
	unsigned char d;

	/*
	 * This is main stuff - enable access to GF1 chip...
	 * I'm not sure, if this will work for card which have
	 * ES1688 chip in another place than 0x220.
         *
         * I used reverse-engineering in DOSEMU. [--jk]
	 *
	 * ULTRINIT.EXE:
	 * 0x230 = 0,2,3
	 * 0x240 = 2,0,1
	 * 0x250 = 2,0,3
	 * 0x260 = 2,2,1
	 */

	spin_lock_irqsave(&es1688->mixer_lock, flags);
	snd_es1688_mixer_write(es1688, 0x40, 0x0b);	/* don't change!!! */
	spin_unlock_irqrestore(&es1688->mixer_lock, flags);

	spin_lock_irqsave(&es1688->reg_lock, flags);
	outb(gus->gf1.port & 0x040 ? 2 : 0, ES1688P(es1688, INIT1));
	outb(0, 0x201);
	outb(gus->gf1.port & 0x020 ? 2 : 0, ES1688P(es1688, INIT1));
	outb(0, 0x201);
	outb(gus->gf1.port & 0x010 ? 3 : 1, ES1688P(es1688, INIT1));
	spin_unlock_irqrestore(&es1688->reg_lock, flags);

	udelay(100);

	snd_gf1_i_write8(gus, SNDRV_GF1_GB_RESET, 0);	/* reset GF1 */
	if (((d = snd_gf1_i_look8(gus, SNDRV_GF1_GB_RESET)) & 0x07) != 0) {
		snd_printdd("[0x%lx] check 1 failed - 0x%x\n", gus->gf1.port, d);
		return -EIO;
	}
	udelay(160);
	snd_gf1_i_write8(gus, SNDRV_GF1_GB_RESET, 1);	/* release reset */
	udelay(160);
	if (((d = snd_gf1_i_look8(gus, SNDRV_GF1_GB_RESET)) & 0x07) != 1) {
		snd_printdd("[0x%lx] check 2 failed - 0x%x\n", gus->gf1.port, d);
		return -EIO;
	}

	return 0;
}