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
struct usbdux_private {scalar_t__ ao_cmd_running; int /*<<< orphan*/  n_ao_urbs; scalar_t__ ao_urbs; } ;
struct comedi_device {struct usbdux_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbdux_unlink_urbs (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbdux_ao_stop(struct comedi_device *dev, int do_unlink)
{
	struct usbdux_private *devpriv = dev->private;

	if (do_unlink && devpriv->ao_urbs)
		usbdux_unlink_urbs(devpriv->ao_urbs, devpriv->n_ao_urbs);

	devpriv->ao_cmd_running = 0;
}