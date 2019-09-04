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
struct comedi_device {scalar_t__ iobase; struct apci3120_private* private; } ;
struct apci3120_private {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  APCI3120_CTRL_EXT_TRIG ; 
 scalar_t__ APCI3120_CTRL_REG ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void apci3120_exttrig_enable(struct comedi_device *dev, bool enable)
{
	struct apci3120_private *devpriv = dev->private;

	if (enable)
		devpriv->ctrl |= APCI3120_CTRL_EXT_TRIG;
	else
		devpriv->ctrl &= ~APCI3120_CTRL_EXT_TRIG;
	outw(devpriv->ctrl, dev->iobase + APCI3120_CTRL_REG);
}