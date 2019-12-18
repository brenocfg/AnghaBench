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
struct intel8x0 {int /*<<< orphan*/  reg_lock; TYPE_1__* card; int /*<<< orphan*/  in_measurement; } ;
struct ichdev {unsigned long reg_offset; int civ; int position; int fragsize1; int size; int lvi; int lvi_frag; int frags; scalar_t__ ack; scalar_t__ ack_reload; scalar_t__ roff_sr; scalar_t__ substream; int /*<<< orphan*/ * bdbar; scalar_t__ physbuf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ICH_BCIS ; 
 int ICH_FIFOE ; 
 int ICH_LVBCI ; 
 int ICH_REG_LVI_MASK ; 
 scalar_t__ ICH_REG_OFF_CIV ; 
 scalar_t__ ICH_REG_OFF_CR ; 
 scalar_t__ ICH_REG_OFF_LVI ; 
 scalar_t__ ICH_REG_OFF_PIV ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int igetbyte (struct intel8x0*,scalar_t__) ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  inl (unsigned long) ; 
 int /*<<< orphan*/  iputbyte (struct intel8x0*,scalar_t__,int) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void snd_intel8x0_update(struct intel8x0 *chip, struct ichdev *ichdev)
{
	unsigned long port = ichdev->reg_offset;
	unsigned long flags;
	int status, civ, i, step;
	int ack = 0;

	spin_lock_irqsave(&chip->reg_lock, flags);
	status = igetbyte(chip, port + ichdev->roff_sr);
	civ = igetbyte(chip, port + ICH_REG_OFF_CIV);
	if (!(status & ICH_BCIS)) {
		step = 0;
	} else if (civ == ichdev->civ) {
		// snd_printd("civ same %d\n", civ);
		step = 1;
		ichdev->civ++;
		ichdev->civ &= ICH_REG_LVI_MASK;
	} else {
		step = civ - ichdev->civ;
		if (step < 0)
			step += ICH_REG_LVI_MASK + 1;
		// if (step != 1)
		//	snd_printd("step = %d, %d -> %d\n", step, ichdev->civ, civ);
		ichdev->civ = civ;
	}

	ichdev->position += step * ichdev->fragsize1;
	if (! chip->in_measurement)
		ichdev->position %= ichdev->size;
	ichdev->lvi += step;
	ichdev->lvi &= ICH_REG_LVI_MASK;
	iputbyte(chip, port + ICH_REG_OFF_LVI, ichdev->lvi);
	for (i = 0; i < step; i++) {
		ichdev->lvi_frag++;
		ichdev->lvi_frag %= ichdev->frags;
		ichdev->bdbar[ichdev->lvi * 2] = cpu_to_le32(ichdev->physbuf + ichdev->lvi_frag * ichdev->fragsize1);
#if 0
	dev_dbg(chip->card->dev,
		"new: bdbar[%i] = 0x%x [0x%x], prefetch = %i, all = 0x%x, 0x%x\n",
	       ichdev->lvi * 2, ichdev->bdbar[ichdev->lvi * 2],
	       ichdev->bdbar[ichdev->lvi * 2 + 1], inb(ICH_REG_OFF_PIV + port),
	       inl(port + 4), inb(port + ICH_REG_OFF_CR));
#endif
		if (--ichdev->ack == 0) {
			ichdev->ack = ichdev->ack_reload;
			ack = 1;
		}
	}
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	if (ack && ichdev->substream) {
		snd_pcm_period_elapsed(ichdev->substream);
	}
	iputbyte(chip, port + ichdev->roff_sr,
		 status & (ICH_FIFOE | ICH_BCIS | ICH_LVBCI));
}