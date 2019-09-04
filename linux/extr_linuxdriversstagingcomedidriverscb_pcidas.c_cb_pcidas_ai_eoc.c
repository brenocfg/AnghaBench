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
struct comedi_device {struct cb_pcidas_private* private; } ;
struct cb_pcidas_private {scalar_t__ pcibar1; } ;

/* Variables and functions */
 int EBUSY ; 
 unsigned int PCIDAS_AI_EOC ; 
 scalar_t__ PCIDAS_AI_REG ; 
 unsigned int inw (scalar_t__) ; 

__attribute__((used)) static int cb_pcidas_ai_eoc(struct comedi_device *dev,
			    struct comedi_subdevice *s,
			    struct comedi_insn *insn,
			    unsigned long context)
{
	struct cb_pcidas_private *devpriv = dev->private;
	unsigned int status;

	status = inw(devpriv->pcibar1 + PCIDAS_AI_REG);
	if (status & PCIDAS_AI_EOC)
		return 0;
	return -EBUSY;
}