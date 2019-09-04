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
struct pcl816_private {int /*<<< orphan*/  dma; } ;
struct comedi_device {struct pcl816_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_isadma_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcl816_free_dma(struct comedi_device *dev)
{
	struct pcl816_private *devpriv = dev->private;

	if (devpriv)
		comedi_isadma_free(devpriv->dma);
}