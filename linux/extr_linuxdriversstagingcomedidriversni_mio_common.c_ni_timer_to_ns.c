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
struct ni_private {int clock_ns; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int ni_timer_to_ns(const struct comedi_device *dev, int timer)
{
	struct ni_private *devpriv = dev->private;

	return devpriv->clock_ns * (timer + 1);
}