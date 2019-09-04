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
 int EBUSY ; 
 int EOVERFLOW ; 
 scalar_t__ RTI800_CLRFLAGS ; 
 scalar_t__ RTI800_CSR ; 
 unsigned char RTI800_CSR_DONE ; 
 unsigned char RTI800_CSR_OVERRUN ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int rti800_ai_eoc(struct comedi_device *dev,
			 struct comedi_subdevice *s,
			 struct comedi_insn *insn,
			 unsigned long context)
{
	unsigned char status;

	status = inb(dev->iobase + RTI800_CSR);
	if (status & RTI800_CSR_OVERRUN) {
		outb(0, dev->iobase + RTI800_CLRFLAGS);
		return -EOVERFLOW;
	}
	if (status & RTI800_CSR_DONE)
		return 0;
	return -EBUSY;
}