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
struct comedi_subdevice {int n_chan; scalar_t__ private; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 int inb (scalar_t__) ; 

__attribute__((used)) static unsigned int pcl730_get_bits(struct comedi_device *dev,
				    struct comedi_subdevice *s)
{
	unsigned long reg = (unsigned long)s->private;
	unsigned int val;

	val = inb(dev->iobase + reg);
	if (s->n_chan > 8)
		val |= (inb(dev->iobase + reg + 1) << 8);
	if (s->n_chan > 16)
		val |= (inb(dev->iobase + reg + 2) << 16);
	if (s->n_chan > 24)
		val |= (inb(dev->iobase + reg + 3) << 24);

	return val;
}