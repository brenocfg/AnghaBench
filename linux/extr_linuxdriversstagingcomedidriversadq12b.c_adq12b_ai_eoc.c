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
struct comedi_insn {int dummy; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ ADQ12B_STINR ; 
 unsigned char ADQ12B_STINR_EOC ; 
 int EBUSY ; 
 unsigned char inb (scalar_t__) ; 

__attribute__((used)) static int adq12b_ai_eoc(struct comedi_device *dev,
			 struct comedi_subdevice *s,
			 struct comedi_insn *insn,
			 unsigned long context)
{
	unsigned char status;

	status = inb(dev->iobase + ADQ12B_STINR);
	if (status & ADQ12B_STINR_EOC)
		return 0;
	return -EBUSY;
}