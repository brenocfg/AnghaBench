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
typedef  int u16 ;
struct das16m1_private {int adc_count; int initial_hw_count; int /*<<< orphan*/  ai_buffer; int /*<<< orphan*/  counter; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; int /*<<< orphan*/  iobase; struct comedi_subdevice* read_subdev; struct das16m1_private* private; } ;
struct comedi_cmd {scalar_t__ stop_src; int stop_arg; int chanlist_len; } ;
struct comedi_async {int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 int DAS16M1_AI_FIFO_SZ ; 
 unsigned int DAS16M1_CS_OVRUN ; 
 scalar_t__ TRIG_COUNT ; 
 int comedi_8254_read (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  insw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void das16m1_handler(struct comedi_device *dev, unsigned int status)
{
	struct das16m1_private *devpriv = dev->private;
	struct comedi_subdevice *s = dev->read_subdev;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	u16 num_samples;
	u16 hw_counter;

	/* figure out how many samples are in fifo */
	hw_counter = comedi_8254_read(devpriv->counter, 1);
	/*
	 * Make sure hardware counter reading is not bogus due to initial
	 * value not having been loaded yet.
	 */
	if (devpriv->adc_count == 0 &&
	    hw_counter == devpriv->initial_hw_count) {
		num_samples = 0;
	} else {
		/*
		 * The calculation of num_samples looks odd, but it uses the
		 * following facts. 16 bit hardware counter is initialized with
		 * value of zero (which really means 0x1000).  The counter
		 * decrements by one on each conversion (when the counter
		 * decrements from zero it goes to 0xffff).  num_samples is a
		 * 16 bit variable, so it will roll over in a similar fashion
		 * to the hardware counter.  Work it out, and this is what you
		 * get.
		 */
		num_samples = -hw_counter - devpriv->adc_count;
	}
	/*  check if we only need some of the points */
	if (cmd->stop_src == TRIG_COUNT) {
		if (num_samples > cmd->stop_arg * cmd->chanlist_len)
			num_samples = cmd->stop_arg * cmd->chanlist_len;
	}
	/*  make sure we don't try to get too many points if fifo has overrun */
	if (num_samples > DAS16M1_AI_FIFO_SZ)
		num_samples = DAS16M1_AI_FIFO_SZ;
	insw(dev->iobase, devpriv->ai_buffer, num_samples);
	comedi_buf_write_samples(s, devpriv->ai_buffer, num_samples);
	devpriv->adc_count += num_samples;

	if (cmd->stop_src == TRIG_COUNT) {
		if (devpriv->adc_count >= cmd->stop_arg * cmd->chanlist_len) {
			/* end of acquisition */
			async->events |= COMEDI_CB_EOA;
		}
	}

	/*
	 * This probably won't catch overruns since the card doesn't generate
	 * overrun interrupts, but we might as well try.
	 */
	if (status & DAS16M1_CS_OVRUN) {
		async->events |= COMEDI_CB_ERROR;
		dev_err(dev->class_dev, "fifo overflow\n");
	}

	comedi_handle_events(dev, s);
}