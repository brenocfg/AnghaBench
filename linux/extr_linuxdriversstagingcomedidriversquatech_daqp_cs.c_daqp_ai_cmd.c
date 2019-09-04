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
struct daqp_private {int /*<<< orphan*/  pacer_div; scalar_t__ stop; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ iobase; struct daqp_private* private; } ;
struct comedi_cmd {scalar_t__ convert_src; int chanlist_len; scalar_t__ stop_src; unsigned long long scan_end_arg; scalar_t__ stop_arg; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_2__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 scalar_t__ DAQP_AI_FIFO_REG ; 
 scalar_t__ DAQP_AUX_REG ; 
 int DAQP_CMD_ARM ; 
 int DAQP_CMD_FIFO_DATA ; 
 scalar_t__ DAQP_CMD_REG ; 
 int DAQP_CMD_RSTF ; 
 int DAQP_CMD_RSTQ ; 
 int DAQP_CTRL_FIFO_INT_ENA ; 
 int DAQP_CTRL_PACER_CLK_5MHZ ; 
 scalar_t__ DAQP_CTRL_REG ; 
 int DAQP_CTRL_TRIG_MODE ; 
 int DAQP_FIFO_SIZE ; 
 int EIO ; 
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ TRIG_TIMER ; 
 unsigned long long comedi_bytes_per_sample (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  daqp_ai_set_one_scanlist_entry (struct comedi_device*,int /*<<< orphan*/ ,int) ; 
 int daqp_clear_events (struct comedi_device*,int) ; 
 int /*<<< orphan*/  daqp_set_pacer (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int daqp_ai_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct daqp_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	int scanlist_start_on_every_entry;
	int threshold;
	int ret;
	int i;

	if (devpriv->stop)
		return -EIO;

	outb(0, dev->iobase + DAQP_AUX_REG);

	/* Reset scan list queue */
	outb(DAQP_CMD_RSTQ, dev->iobase + DAQP_CMD_REG);

	/* Program pacer clock
	 *
	 * There's two modes we can operate in.  If convert_src is
	 * TRIG_TIMER, then convert_arg specifies the time between
	 * each conversion, so we program the pacer clock to that
	 * frequency and set the SCANLIST_START bit on every scanlist
	 * entry.  Otherwise, convert_src is TRIG_NOW, which means
	 * we want the fastest possible conversions, scan_begin_src
	 * is TRIG_TIMER, and scan_begin_arg specifies the time between
	 * each scan, so we program the pacer clock to this frequency
	 * and only set the SCANLIST_START bit on the first entry.
	 */
	daqp_set_pacer(dev, devpriv->pacer_div);

	if (cmd->convert_src == TRIG_TIMER)
		scanlist_start_on_every_entry = 1;
	else
		scanlist_start_on_every_entry = 0;

	/* Program scan list */
	for (i = 0; i < cmd->chanlist_len; i++) {
		int start = (i == 0 || scanlist_start_on_every_entry);

		daqp_ai_set_one_scanlist_entry(dev, cmd->chanlist[i], start);
	}

	/* Now it's time to program the FIFO threshold, basically the
	 * number of samples the card will buffer before it interrupts
	 * the CPU.
	 *
	 * If we don't have a stop count, then use half the size of
	 * the FIFO (the manufacturer's recommendation).  Consider
	 * that the FIFO can hold 2K samples (4K bytes).  With the
	 * threshold set at half the FIFO size, we have a margin of
	 * error of 1024 samples.  At the chip's maximum sample rate
	 * of 100,000 Hz, the CPU would have to delay interrupt
	 * service for a full 10 milliseconds in order to lose data
	 * here (as opposed to higher up in the kernel).  I've never
	 * seen it happen.  However, for slow sample rates it may
	 * buffer too much data and introduce too much delay for the
	 * user application.
	 *
	 * If we have a stop count, then things get more interesting.
	 * If the stop count is less than the FIFO size (actually
	 * three-quarters of the FIFO size - see below), we just use
	 * the stop count itself as the threshold, the card interrupts
	 * us when that many samples have been taken, and we kill the
	 * acquisition at that point and are done.  If the stop count
	 * is larger than that, then we divide it by 2 until it's less
	 * than three quarters of the FIFO size (we always leave the
	 * top quarter of the FIFO as protection against sluggish CPU
	 * interrupt response) and use that as the threshold.  So, if
	 * the stop count is 4000 samples, we divide by two twice to
	 * get 1000 samples, use that as the threshold, take four
	 * interrupts to get our 4000 samples and are done.
	 *
	 * The algorithm could be more clever.  For example, if 81000
	 * samples are requested, we could set the threshold to 1500
	 * samples and take 54 interrupts to get 81000.  But 54 isn't
	 * a power of two, so this algorithm won't find that option.
	 * Instead, it'll set the threshold at 1266 and take 64
	 * interrupts to get 81024 samples, of which the last 24 will
	 * be discarded... but we won't get the last interrupt until
	 * they've been collected.  To find the first option, the
	 * computer could look at the prime decomposition of the
	 * sample count (81000 = 3^4 * 5^3 * 2^3) and factor it into a
	 * threshold (1500 = 3 * 5^3 * 2^2) and an interrupt count (54
	 * = 3^3 * 2).  Hmmm... a one-line while loop or prime
	 * decomposition of integers... I'll leave it the way it is.
	 *
	 * I'll also note a mini-race condition before ignoring it in
	 * the code.  Let's say we're taking 4000 samples, as before.
	 * After 1000 samples, we get an interrupt.  But before that
	 * interrupt is completely serviced, another sample is taken
	 * and loaded into the FIFO.  Since the interrupt handler
	 * empties the FIFO before returning, it will read 1001 samples.
	 * If that happens four times, we'll end up taking 4004 samples,
	 * not 4000.  The interrupt handler will discard the extra four
	 * samples (by halting the acquisition with four samples still
	 * in the FIFO), but we will have to wait for them.
	 *
	 * In short, this code works pretty well, but for either of
	 * the two reasons noted, might end up waiting for a few more
	 * samples than actually requested.  Shouldn't make too much
	 * of a difference.
	 */

	/* Save away the number of conversions we should perform, and
	 * compute the FIFO threshold (in bytes, not samples - that's
	 * why we multiple devpriv->count by 2 = sizeof(sample))
	 */

	if (cmd->stop_src == TRIG_COUNT) {
		unsigned long long nsamples;
		unsigned long long nbytes;

		nsamples = (unsigned long long)cmd->stop_arg *
			   cmd->scan_end_arg;
		nbytes = nsamples * comedi_bytes_per_sample(s);
		while (nbytes > DAQP_FIFO_SIZE * 3 / 4)
			nbytes /= 2;
		threshold = nbytes;
	} else {
		threshold = DAQP_FIFO_SIZE / 2;
	}

	/* Reset data FIFO (see page 28 of DAQP User's Manual) */

	outb(DAQP_CMD_RSTF, dev->iobase + DAQP_CMD_REG);

	/* Set FIFO threshold.  First two bytes are near-empty
	 * threshold, which is unused; next two bytes are near-full
	 * threshold.  We computed the number of bytes we want in the
	 * FIFO when the interrupt is generated, what the card wants
	 * is actually the number of available bytes left in the FIFO
	 * when the interrupt is to happen.
	 */

	outb(0x00, dev->iobase + DAQP_AI_FIFO_REG);
	outb(0x00, dev->iobase + DAQP_AI_FIFO_REG);

	outb((DAQP_FIFO_SIZE - threshold) & 0xff,
	     dev->iobase + DAQP_AI_FIFO_REG);
	outb((DAQP_FIFO_SIZE - threshold) >> 8, dev->iobase + DAQP_AI_FIFO_REG);

	/* Set trigger - continuous, internal */
	outb(DAQP_CTRL_TRIG_MODE | DAQP_CTRL_PACER_CLK_5MHZ |
	     DAQP_CTRL_FIFO_INT_ENA, dev->iobase + DAQP_CTRL_REG);

	ret = daqp_clear_events(dev, 100);
	if (ret)
		return ret;

	/* Start conversion */
	outb(DAQP_CMD_ARM | DAQP_CMD_FIFO_DATA, dev->iobase + DAQP_CMD_REG);

	return 0;
}