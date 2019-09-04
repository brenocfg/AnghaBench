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
struct pcl818_private {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  read_subdev; struct pcl818_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_legacy_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  pcl818_ai_cancel (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcl818_free_dma (struct comedi_device*) ; 
 int /*<<< orphan*/  pcl818_reset (struct comedi_device*) ; 

__attribute__((used)) static void pcl818_detach(struct comedi_device *dev)
{
	struct pcl818_private *devpriv = dev->private;

	if (devpriv) {
		pcl818_ai_cancel(dev, dev->read_subdev);
		pcl818_reset(dev);
	}
	pcl818_free_dma(dev);
	comedi_legacy_detach(dev);
}