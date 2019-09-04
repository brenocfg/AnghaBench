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
struct waveform_private {int /*<<< orphan*/  ao_timer; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct waveform_private* private; } ;
struct TYPE_2__ {int /*<<< orphan*/ * inttrig; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ in_softirq () ; 

__attribute__((used)) static int waveform_ao_cancel(struct comedi_device *dev,
			      struct comedi_subdevice *s)
{
	struct waveform_private *devpriv = dev->private;

	s->async->inttrig = NULL;
	if (in_softirq()) {
		/* Assume we were called from the timer routine itself. */
		del_timer(&devpriv->ao_timer);
	} else {
		del_timer_sync(&devpriv->ao_timer);
	}
	return 0;
}