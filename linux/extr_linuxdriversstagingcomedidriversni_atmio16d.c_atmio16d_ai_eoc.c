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
 scalar_t__ AD_CLEAR_REG ; 
 int EBUSY ; 
 int EOVERFLOW ; 
 unsigned int STAT_AD_CONVAVAIL ; 
 unsigned int STAT_AD_OVERFLOW ; 
 scalar_t__ STAT_REG ; 
 unsigned int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int atmio16d_ai_eoc(struct comedi_device *dev,
			   struct comedi_subdevice *s,
			   struct comedi_insn *insn,
			   unsigned long context)
{
	unsigned int status;

	status = inw(dev->iobase + STAT_REG);
	if (status & STAT_AD_CONVAVAIL)
		return 0;
	if (status & STAT_AD_OVERFLOW) {
		outw(0, dev->iobase + AD_CLEAR_REG);
		return -EOVERFLOW;
	}
	return -EBUSY;
}