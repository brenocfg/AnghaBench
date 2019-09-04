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
struct comedi_insn {int n; } ;
struct comedi_device {struct apci1564_private* private; } ;
struct apci1564_private {scalar_t__ timer; } ;

/* Variables and functions */
 scalar_t__ ADDI_TCW_RELOAD_REG ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

__attribute__((used)) static int apci1564_timer_insn_write(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     struct comedi_insn *insn,
				     unsigned int *data)
{
	struct apci1564_private *devpriv = dev->private;

	/* just write the last last to the reload register */
	if (insn->n) {
		unsigned int val = data[insn->n - 1];

		outl(val, devpriv->timer + ADDI_TCW_RELOAD_REG);
	}

	return insn->n;
}