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
struct pcl816_private {int ai_cmd_canceled; scalar_t__ ai_cmd_running; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  pacer; scalar_t__ iobase; struct pcl816_private* private; } ;

/* Variables and functions */
 scalar_t__ PCL816_CTRL_REG ; 
 int /*<<< orphan*/  comedi_8254_pacer_enable (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pcl816_ai_clear_eoc (struct comedi_device*) ; 

__attribute__((used)) static int pcl816_ai_cancel(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	struct pcl816_private *devpriv = dev->private;

	if (!devpriv->ai_cmd_running)
		return 0;

	outb(0, dev->iobase + PCL816_CTRL_REG);
	pcl816_ai_clear_eoc(dev);

	comedi_8254_pacer_enable(dev->pacer, 1, 2, false);

	devpriv->ai_cmd_running = 0;
	devpriv->ai_cmd_canceled = 1;

	return 0;
}