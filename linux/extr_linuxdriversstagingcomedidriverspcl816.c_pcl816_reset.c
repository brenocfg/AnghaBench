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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ PCL816_CTRL_REG ; 
 scalar_t__ PCL816_DO_DI_LSB_REG ; 
 scalar_t__ PCL816_DO_DI_MSB_REG ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pcl816_ai_clear_eoc (struct comedi_device*) ; 
 int /*<<< orphan*/  pcl816_ai_set_chan_range (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcl816_reset(struct comedi_device *dev)
{
	outb(0, dev->iobase + PCL816_CTRL_REG);
	pcl816_ai_set_chan_range(dev, 0, 0);
	pcl816_ai_clear_eoc(dev);

	/* set all digital outputs low */
	outb(0, dev->iobase + PCL816_DO_DI_LSB_REG);
	outb(0, dev->iobase + PCL816_DO_DI_MSB_REG);
}