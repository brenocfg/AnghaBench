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
typedef  scalar_t__ u64 ;
struct waveform_private {scalar_t__ ai_convert_time; unsigned int wf_current; unsigned int ai_convert_period; int ai_scan_period; unsigned int wf_period; int /*<<< orphan*/  ai_timer; struct comedi_device* dev; } ;
struct timer_list {int dummy; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {struct comedi_subdevice* read_subdev; } ;
struct comedi_cmd {unsigned int* chanlist; int scan_end_arg; scalar_t__ stop_src; scalar_t__ stop_arg; } ;
struct comedi_async {size_t cur_chan; scalar_t__ scan_progress; scalar_t__ scans_done; int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  CR_CHAN (unsigned int) ; 
 int /*<<< orphan*/  CR_RANGE (unsigned int) ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  ai_timer ; 
 scalar_t__ comedi_buf_write_samples (struct comedi_subdevice*,unsigned short*,int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 unsigned int comedi_nsamples_left (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 struct waveform_private* devpriv ; 
 unsigned short fake_waveform (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct waveform_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ usecs_to_jiffies (unsigned int) ; 

__attribute__((used)) static void waveform_ai_timer(struct timer_list *t)
{
	struct waveform_private *devpriv = from_timer(devpriv, t, ai_timer);
	struct comedi_device *dev = devpriv->dev;
	struct comedi_subdevice *s = dev->read_subdev;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	u64 now;
	unsigned int nsamples;
	unsigned int time_increment;

	now = ktime_to_us(ktime_get());
	nsamples = comedi_nsamples_left(s, UINT_MAX);

	while (nsamples && devpriv->ai_convert_time < now) {
		unsigned int chanspec = cmd->chanlist[async->cur_chan];
		unsigned short sample;

		sample = fake_waveform(dev, CR_CHAN(chanspec),
				       CR_RANGE(chanspec), devpriv->wf_current);
		if (comedi_buf_write_samples(s, &sample, 1) == 0)
			goto overrun;
		time_increment = devpriv->ai_convert_period;
		if (async->scan_progress == 0) {
			/* done last conversion in scan, so add dead time */
			time_increment += devpriv->ai_scan_period -
					  devpriv->ai_convert_period *
					  cmd->scan_end_arg;
		}
		devpriv->wf_current += time_increment;
		if (devpriv->wf_current >= devpriv->wf_period)
			devpriv->wf_current %= devpriv->wf_period;
		devpriv->ai_convert_time += time_increment;
		nsamples--;
	}

	if (cmd->stop_src == TRIG_COUNT && async->scans_done >= cmd->stop_arg) {
		async->events |= COMEDI_CB_EOA;
	} else {
		if (devpriv->ai_convert_time > now)
			time_increment = devpriv->ai_convert_time - now;
		else
			time_increment = 1;
		mod_timer(&devpriv->ai_timer,
			  jiffies + usecs_to_jiffies(time_increment));
	}

overrun:
	comedi_handle_events(dev, s);
}