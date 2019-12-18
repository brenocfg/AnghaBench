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
typedef  int u32 ;
struct snd_als300 {int revision; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int DRAM_MODE_2 ; 
 int /*<<< orphan*/  DRAM_WRITE_CONTROL ; 
 int /*<<< orphan*/  IRQ_ENABLE ; 
 int /*<<< orphan*/  MISC_CONTROL ; 
 int MMUTE_NORMAL ; 
 int /*<<< orphan*/  MUS_VOC_VOL ; 
 int /*<<< orphan*/  PLAYBACK_CONTROL ; 
 int TRANSFER_START ; 
 int VMUTE_NORMAL ; 
 int WRITE_TRANS_START ; 
 int snd_als300_gcr_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_als300_gcr_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_als300_set_irq_flag (struct snd_als300*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_als300_init(struct snd_als300 *chip)
{
	unsigned long flags;
	u32 tmp;
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	chip->revision = (snd_als300_gcr_read(chip->port, MISC_CONTROL) >> 16)
								& 0x0000000F;
	/* Setup DRAM */
	tmp = snd_als300_gcr_read(chip->port, DRAM_WRITE_CONTROL);
	snd_als300_gcr_write(chip->port, DRAM_WRITE_CONTROL,
						(tmp | DRAM_MODE_2)
						& ~WRITE_TRANS_START);

	/* Enable IRQ output */
	snd_als300_set_irq_flag(chip, IRQ_ENABLE);

	/* Unmute hardware devices so their outputs get routed to
	 * the onboard mixer */
	tmp = snd_als300_gcr_read(chip->port, MISC_CONTROL);
	snd_als300_gcr_write(chip->port, MISC_CONTROL,
			tmp | VMUTE_NORMAL | MMUTE_NORMAL);

	/* Reset volumes */
	snd_als300_gcr_write(chip->port, MUS_VOC_VOL, 0);

	/* Make sure playback transfer is stopped */
	tmp = snd_als300_gcr_read(chip->port, PLAYBACK_CONTROL);
	snd_als300_gcr_write(chip->port, PLAYBACK_CONTROL,
			tmp & ~TRANSFER_START);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
}