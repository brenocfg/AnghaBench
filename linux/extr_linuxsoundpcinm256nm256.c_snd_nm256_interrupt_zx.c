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
typedef  int u8 ;
typedef  int u32 ;
struct nm256 {int /*<<< orphan*/  reg_lock; TYPE_1__* card; scalar_t__ badintrcount; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  NM2_ACK_INT (struct nm256*,int) ; 
 int NM2_MISC_INT_1 ; 
 int NM2_MISC_INT_2 ; 
 int NM2_PLAYBACK_INT ; 
 int NM2_RECORD_INT ; 
 int /*<<< orphan*/  NM_INT_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  snd_nm256_capture_update (struct nm256*) ; 
 int /*<<< orphan*/  snd_nm256_intr_check (struct nm256*) ; 
 int /*<<< orphan*/  snd_nm256_playback_update (struct nm256*) ; 
 int snd_nm256_readb (struct nm256*,int) ; 
 int snd_nm256_readl (struct nm256*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_nm256_writeb (struct nm256*,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
snd_nm256_interrupt_zx(int irq, void *dev_id)
{
	struct nm256 *chip = dev_id;
	u32 status;
	u8 cbyte;

	status = snd_nm256_readl(chip, NM_INT_REG);

	/* Not ours. */
	if (status == 0)
		return snd_nm256_intr_check(chip);

	chip->badintrcount = 0;

	/* Rather boring; check for individual interrupts and process them. */

	spin_lock(&chip->reg_lock);
	if (status & NM2_PLAYBACK_INT) {
		status &= ~NM2_PLAYBACK_INT;
		NM2_ACK_INT(chip, NM2_PLAYBACK_INT);
		snd_nm256_playback_update(chip);
	}

	if (status & NM2_RECORD_INT) {
		status &= ~NM2_RECORD_INT;
		NM2_ACK_INT(chip, NM2_RECORD_INT);
		snd_nm256_capture_update(chip);
	}

	if (status & NM2_MISC_INT_1) {
		status &= ~NM2_MISC_INT_1;
		NM2_ACK_INT(chip, NM2_MISC_INT_1);
		dev_dbg(chip->card->dev, "NM256: Got misc interrupt #1\n");
		cbyte = snd_nm256_readb(chip, 0x400);
		snd_nm256_writeb(chip, 0x400, cbyte | 2);
	}

	if (status & NM2_MISC_INT_2) {
		status &= ~NM2_MISC_INT_2;
		NM2_ACK_INT(chip, NM2_MISC_INT_2);
		dev_dbg(chip->card->dev, "NM256: Got misc interrupt #2\n");
		cbyte = snd_nm256_readb(chip, 0x400);
		snd_nm256_writeb(chip, 0x400, cbyte & ~2);
	}

	/* Unknown interrupt. */
	if (status) {
		dev_dbg(chip->card->dev,
			"NM256: Fire in the hole! Unknown status 0x%x\n",
			   status);
		/* Pray. */
		NM2_ACK_INT(chip, status);
	}

	spin_unlock(&chip->reg_lock);
	return IRQ_HANDLED;
}