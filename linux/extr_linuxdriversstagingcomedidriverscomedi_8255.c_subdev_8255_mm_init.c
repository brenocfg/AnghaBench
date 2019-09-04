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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int __subdev_8255_init (struct comedi_device*,struct comedi_subdevice*,int (*) (struct comedi_device*,int,int,int,unsigned long),unsigned long,int) ; 

int subdev_8255_mm_init(struct comedi_device *dev, struct comedi_subdevice *s,
			int (*io)(struct comedi_device *dev, int dir, int port,
				  int data, unsigned long regbase),
			unsigned long regbase)
{
	return __subdev_8255_init(dev, s, io, regbase, true);
}