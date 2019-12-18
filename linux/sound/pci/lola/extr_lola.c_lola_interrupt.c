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
struct lola {TYPE_1__* pcm; int /*<<< orphan*/  reg_lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int num_streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAR0 ; 
 int /*<<< orphan*/  BAR1 ; 
 size_t CAPT ; 
 int /*<<< orphan*/  CORBSTS ; 
 int /*<<< orphan*/  DIINTSTS ; 
 int /*<<< orphan*/  DINTSTS ; 
 int /*<<< orphan*/  DOINTSTS ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 unsigned char LOLA_CORB_INT_MASK ; 
 unsigned int LOLA_DINT_CTRL ; 
 unsigned int LOLA_DINT_FIFOERR ; 
 unsigned int LOLA_DINT_MUERR ; 
 unsigned int LOLA_DSD_STS_BCIS ; 
 unsigned int LOLA_DSD_STS_DESE ; 
 unsigned char LOLA_RIRB_INT_MASK ; 
 int MAX_STREAM_IN_COUNT ; 
 size_t PLAY ; 
 int /*<<< orphan*/  RIRBSTS ; 
 int /*<<< orphan*/  STS ; 
 unsigned int lola_dsd_read (struct lola*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lola_dsd_write (struct lola*,int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  lola_pcm_update (struct lola*,TYPE_1__*,unsigned int) ; 
 unsigned char lola_readb (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int lola_readl (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lola_update_rirb (struct lola*) ; 
 int /*<<< orphan*/  lola_writeb (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  lola_writel (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t lola_interrupt(int irq, void *dev_id)
{
	struct lola *chip = dev_id;
	unsigned int notify_ins, notify_outs, error_ins, error_outs;
	int handled = 0;
	int i;

	notify_ins = notify_outs = error_ins = error_outs = 0;
	spin_lock(&chip->reg_lock);
	for (;;) {
		unsigned int status, in_sts, out_sts;
		unsigned int reg;

		status = lola_readl(chip, BAR1, DINTSTS);
		if (!status || status == -1)
			break;

		in_sts = lola_readl(chip, BAR1, DIINTSTS);
		out_sts = lola_readl(chip, BAR1, DOINTSTS);

		/* clear Input Interrupts */
		for (i = 0; in_sts && i < chip->pcm[CAPT].num_streams; i++) {
			if (!(in_sts & (1 << i)))
				continue;
			in_sts &= ~(1 << i);
			reg = lola_dsd_read(chip, i, STS);
			if (reg & LOLA_DSD_STS_DESE) /* error */
				error_ins |= (1 << i);
			if (reg & LOLA_DSD_STS_BCIS) /* notify */
				notify_ins |= (1 << i);
			/* clear */
			lola_dsd_write(chip, i, STS, reg);
		}

		/* clear Output Interrupts */
		for (i = 0; out_sts && i < chip->pcm[PLAY].num_streams; i++) {
			if (!(out_sts & (1 << i)))
				continue;
			out_sts &= ~(1 << i);
			reg = lola_dsd_read(chip, i + MAX_STREAM_IN_COUNT, STS);
			if (reg & LOLA_DSD_STS_DESE) /* error */
				error_outs |= (1 << i);
			if (reg & LOLA_DSD_STS_BCIS) /* notify */
				notify_outs |= (1 << i);
			lola_dsd_write(chip, i + MAX_STREAM_IN_COUNT, STS, reg);
		}

		if (status & LOLA_DINT_CTRL) {
			unsigned char rbsts; /* ring status is byte access */
			rbsts = lola_readb(chip, BAR0, RIRBSTS);
			rbsts &= LOLA_RIRB_INT_MASK;
			if (rbsts)
				lola_writeb(chip, BAR0, RIRBSTS, rbsts);
			rbsts = lola_readb(chip, BAR0, CORBSTS);
			rbsts &= LOLA_CORB_INT_MASK;
			if (rbsts)
				lola_writeb(chip, BAR0, CORBSTS, rbsts);

			lola_update_rirb(chip);
		}

		if (status & (LOLA_DINT_FIFOERR | LOLA_DINT_MUERR)) {
			/* clear global fifo error interrupt */
			lola_writel(chip, BAR1, DINTSTS,
				    (status & (LOLA_DINT_FIFOERR | LOLA_DINT_MUERR)));
		}
		handled = 1;
	}
	spin_unlock(&chip->reg_lock);

	lola_pcm_update(chip, &chip->pcm[CAPT], notify_ins);
	lola_pcm_update(chip, &chip->pcm[PLAY], notify_outs);

	return IRQ_RETVAL(handled);
}