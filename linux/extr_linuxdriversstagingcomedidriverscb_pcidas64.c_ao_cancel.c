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
struct pcidas64_private {scalar_t__ main_iobase; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct pcidas64_private* private; } ;

/* Variables and functions */
 scalar_t__ DAC_CONTROL0_REG ; 
 int /*<<< orphan*/  abort_dma (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int ao_cancel(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct pcidas64_private *devpriv = dev->private;

	writew(0x0, devpriv->main_iobase + DAC_CONTROL0_REG);
	abort_dma(dev, 0);
	return 0;
}