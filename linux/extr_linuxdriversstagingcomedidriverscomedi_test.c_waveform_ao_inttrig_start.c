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
struct TYPE_2__ {scalar_t__ expires; } ;
struct waveform_private {TYPE_1__ ao_timer; int /*<<< orphan*/  ao_scan_period; int /*<<< orphan*/  ao_last_scan_time; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {struct waveform_private* private; } ;
struct comedi_cmd {unsigned int start_arg; } ;
struct comedi_async {int /*<<< orphan*/ * inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_to_us (int /*<<< orphan*/ ) ; 
 scalar_t__ usecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int waveform_ao_inttrig_start(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     unsigned int trig_num)
{
	struct waveform_private *devpriv = dev->private;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;

	if (trig_num != cmd->start_arg)
		return -EINVAL;

	async->inttrig = NULL;

	devpriv->ao_last_scan_time = ktime_to_us(ktime_get());
	devpriv->ao_timer.expires =
		jiffies + usecs_to_jiffies(devpriv->ao_scan_period);
	add_timer(&devpriv->ao_timer);

	return 1;
}