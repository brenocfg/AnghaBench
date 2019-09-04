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
struct das08_private_struct {int /*<<< orphan*/  do_mux_bits; } ;
struct comedi_subdevice {unsigned int state; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; scalar_t__ iobase; struct das08_private_struct* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAS08_CONTROL_DO (unsigned int) ; 
 int /*<<< orphan*/  DAS08_CONTROL_DO_MASK ; 
 scalar_t__ DAS08_CONTROL_REG ; 
 scalar_t__ comedi_dio_update_state (struct comedi_subdevice*,unsigned int*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int das08_do_insn_bits(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn, unsigned int *data)
{
	struct das08_private_struct *devpriv = dev->private;

	if (comedi_dio_update_state(s, data)) {
		/* prevent race with setting of analog input mux */
		spin_lock(&dev->spinlock);
		devpriv->do_mux_bits &= ~DAS08_CONTROL_DO_MASK;
		devpriv->do_mux_bits |= DAS08_CONTROL_DO(s->state);
		outb(devpriv->do_mux_bits, dev->iobase + DAS08_CONTROL_REG);
		spin_unlock(&dev->spinlock);
	}

	data[1] = s->state;

	return insn->n;
}