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
struct waveform_private {int /*<<< orphan*/  ai_timer; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct waveform_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ in_softirq () ; 

__attribute__((used)) static int waveform_ai_cancel(struct comedi_device *dev,
			      struct comedi_subdevice *s)
{
	struct waveform_private *devpriv = dev->private;

	if (in_softirq()) {
		/* Assume we were called from the timer routine itself. */
		del_timer(&devpriv->ai_timer);
	} else {
		del_timer_sync(&devpriv->ai_timer);
	}
	return 0;
}