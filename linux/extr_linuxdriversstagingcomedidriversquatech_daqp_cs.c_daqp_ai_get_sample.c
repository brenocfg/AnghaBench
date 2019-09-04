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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ DAQP_AI_FIFO_REG ; 
 unsigned int comedi_offset_munge (struct comedi_subdevice*,unsigned int) ; 
 int inb (scalar_t__) ; 

__attribute__((used)) static unsigned int daqp_ai_get_sample(struct comedi_device *dev,
				       struct comedi_subdevice *s)
{
	unsigned int val;

	/*
	 * Get a two's complement sample from the FIFO and
	 * return the munged offset binary value.
	 */
	val = inb(dev->iobase + DAQP_AI_FIFO_REG);
	val |= inb(dev->iobase + DAQP_AI_FIFO_REG) << 8;
	return comedi_offset_munge(s, val);
}