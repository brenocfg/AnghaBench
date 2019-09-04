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
struct comedi_subdevice {struct apci2032_int_private* private; } ;
struct comedi_device {scalar_t__ iobase; } ;
struct apci2032_int_private {int active; scalar_t__ enabled_isns; } ;

/* Variables and functions */
 scalar_t__ APCI2032_INT_CTRL_REG ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static void apci2032_int_stop(struct comedi_device *dev,
			      struct comedi_subdevice *s)
{
	struct apci2032_int_private *subpriv = s->private;

	subpriv->active = false;
	subpriv->enabled_isns = 0;
	outl(0x0, dev->iobase + APCI2032_INT_CTRL_REG);
}