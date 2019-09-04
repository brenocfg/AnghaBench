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
struct rtd_private {int fifosz; int xfer_count; int ai_count; int /*<<< orphan*/  flags; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ mmio; struct rtd_private* private; } ;
struct comedi_cmd {int chanlist_len; int scan_begin_src; int flags; int scan_begin_arg; int stop_src; int stop_arg; int convert_src; int convert_arg; int /*<<< orphan*/  chanlist; } ;
struct TYPE_2__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDF_ROUND_NEAREST ; 
 int CMDF_WAKE_EOS ; 
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  IRQM_ADC_ABOUT_CNT ; 
 scalar_t__ LAS0_ACNT ; 
 scalar_t__ LAS0_ACNT_STOP_ENABLE ; 
 scalar_t__ LAS0_ADC_CONVERSION ; 
 scalar_t__ LAS0_ADC_FIFO_CLEAR ; 
 scalar_t__ LAS0_BCLK ; 
 scalar_t__ LAS0_BURST_START ; 
 scalar_t__ LAS0_CLEAR ; 
 scalar_t__ LAS0_IT ; 
 scalar_t__ LAS0_OVERRUN ; 
 scalar_t__ LAS0_PACER ; 
 scalar_t__ LAS0_PACER_SELECT ; 
 scalar_t__ LAS0_PACER_START ; 
 scalar_t__ LAS0_PACER_STOP ; 
 scalar_t__ LAS0_PCLK ; 
 int /*<<< orphan*/  SEND_EOS ; 
 int TRANS_TARGET_PERIOD ; 
#define  TRIG_COUNT 131 
#define  TRIG_EXT 130 
#define  TRIG_NONE 129 
#define  TRIG_TIMER 128 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 
 int /*<<< orphan*/  rtd_load_channelgain_list (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int rtd_ns_to_timer (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int rtd_ai_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct rtd_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	int timer;

	/* stop anything currently running */
	/* pacer stop source: SOFTWARE */
	writel(0, dev->mmio + LAS0_PACER_STOP);
	writel(0, dev->mmio + LAS0_PACER);	/* stop pacer */
	writel(0, dev->mmio + LAS0_ADC_CONVERSION);
	writew(0, dev->mmio + LAS0_IT);
	writel(0, dev->mmio + LAS0_ADC_FIFO_CLEAR);
	writel(0, dev->mmio + LAS0_OVERRUN);

	/* start configuration */
	/* load channel list and reset CGT */
	rtd_load_channelgain_list(dev, cmd->chanlist_len, cmd->chanlist);

	/* setup the common case and override if needed */
	if (cmd->chanlist_len > 1) {
		/* pacer start source: SOFTWARE */
		writel(0, dev->mmio + LAS0_PACER_START);
		/* burst trigger source: PACER */
		writel(1, dev->mmio + LAS0_BURST_START);
		/* ADC conversion trigger source: BURST */
		writel(2, dev->mmio + LAS0_ADC_CONVERSION);
	} else {		/* single channel */
		/* pacer start source: SOFTWARE */
		writel(0, dev->mmio + LAS0_PACER_START);
		/* ADC conversion trigger source: PACER */
		writel(1, dev->mmio + LAS0_ADC_CONVERSION);
	}
	writel((devpriv->fifosz / 2 - 1) & 0xffff, dev->mmio + LAS0_ACNT);

	if (cmd->scan_begin_src == TRIG_TIMER) {
		/* scan_begin_arg is in nanoseconds */
		/* find out how many samples to wait before transferring */
		if (cmd->flags & CMDF_WAKE_EOS) {
			/*
			 * this may generate un-sustainable interrupt rates
			 * the application is responsible for doing the
			 * right thing
			 */
			devpriv->xfer_count = cmd->chanlist_len;
			devpriv->flags |= SEND_EOS;
		} else {
			/* arrange to transfer data periodically */
			devpriv->xfer_count =
			    (TRANS_TARGET_PERIOD * cmd->chanlist_len) /
			    cmd->scan_begin_arg;
			if (devpriv->xfer_count < cmd->chanlist_len) {
				/* transfer after each scan (and avoid 0) */
				devpriv->xfer_count = cmd->chanlist_len;
			} else {	/* make a multiple of scan length */
				devpriv->xfer_count =
				    DIV_ROUND_UP(devpriv->xfer_count,
						 cmd->chanlist_len);
				devpriv->xfer_count *= cmd->chanlist_len;
			}
			devpriv->flags |= SEND_EOS;
		}
		if (devpriv->xfer_count >= (devpriv->fifosz / 2)) {
			/* out of counter range, use 1/2 fifo instead */
			devpriv->xfer_count = 0;
			devpriv->flags &= ~SEND_EOS;
		} else {
			/* interrupt for each transfer */
			writel((devpriv->xfer_count - 1) & 0xffff,
			       dev->mmio + LAS0_ACNT);
		}
	} else {		/* unknown timing, just use 1/2 FIFO */
		devpriv->xfer_count = 0;
		devpriv->flags &= ~SEND_EOS;
	}
	/* pacer clock source: INTERNAL 8MHz */
	writel(1, dev->mmio + LAS0_PACER_SELECT);
	/* just interrupt, don't stop */
	writel(1, dev->mmio + LAS0_ACNT_STOP_ENABLE);

	/* BUG??? these look like enumerated values, but they are bit fields */

	/* First, setup when to stop */
	switch (cmd->stop_src) {
	case TRIG_COUNT:	/* stop after N scans */
		devpriv->ai_count = cmd->stop_arg * cmd->chanlist_len;
		if ((devpriv->xfer_count > 0) &&
		    (devpriv->xfer_count > devpriv->ai_count)) {
			devpriv->xfer_count = devpriv->ai_count;
		}
		break;

	case TRIG_NONE:	/* stop when cancel is called */
		devpriv->ai_count = -1;	/* read forever */
		break;
	}

	/* Scan timing */
	switch (cmd->scan_begin_src) {
	case TRIG_TIMER:	/* periodic scanning */
		timer = rtd_ns_to_timer(&cmd->scan_begin_arg,
					CMDF_ROUND_NEAREST);
		/* set PACER clock */
		writel(timer & 0xffffff, dev->mmio + LAS0_PCLK);

		break;

	case TRIG_EXT:
		/* pacer start source: EXTERNAL */
		writel(1, dev->mmio + LAS0_PACER_START);
		break;
	}

	/* Sample timing within a scan */
	switch (cmd->convert_src) {
	case TRIG_TIMER:	/* periodic */
		if (cmd->chanlist_len > 1) {
			/* only needed for multi-channel */
			timer = rtd_ns_to_timer(&cmd->convert_arg,
						CMDF_ROUND_NEAREST);
			/* setup BURST clock */
			writel(timer & 0x3ff, dev->mmio + LAS0_BCLK);
		}

		break;

	case TRIG_EXT:		/* external */
		/* burst trigger source: EXTERNAL */
		writel(2, dev->mmio + LAS0_BURST_START);
		break;
	}
	/* end configuration */

	/*
	 * This doesn't seem to work.  There is no way to clear an interrupt
	 * that the priority controller has queued!
	 */
	writew(~0, dev->mmio + LAS0_CLEAR);
	readw(dev->mmio + LAS0_CLEAR);

	/* TODO: allow multiple interrupt sources */
	/* transfer every N samples */
	writew(IRQM_ADC_ABOUT_CNT, dev->mmio + LAS0_IT);

	/* BUG: start_src is ASSUMED to be TRIG_NOW */
	/* BUG? it seems like things are running before the "start" */
	readl(dev->mmio + LAS0_PACER);	/* start pacer */
	return 0;
}