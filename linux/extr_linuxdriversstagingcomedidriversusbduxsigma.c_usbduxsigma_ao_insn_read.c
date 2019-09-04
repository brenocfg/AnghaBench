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
struct usbduxsigma_private {int /*<<< orphan*/  mut; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int dummy; } ;
struct comedi_device {struct usbduxsigma_private* private; } ;

/* Variables and functions */
 int comedi_readback_insn_read (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int usbduxsigma_ao_insn_read(struct comedi_device *dev,
				    struct comedi_subdevice *s,
				    struct comedi_insn *insn,
				    unsigned int *data)
{
	struct usbduxsigma_private *devpriv = dev->private;
	int ret;

	mutex_lock(&devpriv->mut);
	ret = comedi_readback_insn_read(dev, s, insn, data);
	mutex_unlock(&devpriv->mut);

	return ret;
}