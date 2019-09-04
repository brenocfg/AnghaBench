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
struct ni_private {int /*<<< orphan*/  dio_output; scalar_t__ serial_interval_ns; } ;
struct comedi_subdevice {int /*<<< orphan*/  state; } ;
struct comedi_insn {int n; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  NISTC_DIO_IN_REG ; 
 int /*<<< orphan*/  NISTC_DIO_OUT_PARALLEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NISTC_DIO_OUT_PARALLEL_MASK ; 
 int /*<<< orphan*/  NISTC_DIO_OUT_REG ; 
 unsigned int NISTC_DIO_SDIN ; 
 unsigned int NISTC_DIO_SDOUT ; 
 scalar_t__ comedi_dio_update_state (struct comedi_subdevice*,unsigned int*) ; 
 unsigned int ni_stc_readw (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_dio_insn_bits(struct comedi_device *dev,
			    struct comedi_subdevice *s,
			    struct comedi_insn *insn,
			    unsigned int *data)
{
	struct ni_private *devpriv = dev->private;

	/* Make sure we're not using the serial part of the dio */
	if ((data[0] & (NISTC_DIO_SDIN | NISTC_DIO_SDOUT)) &&
	    devpriv->serial_interval_ns)
		return -EBUSY;

	if (comedi_dio_update_state(s, data)) {
		devpriv->dio_output &= ~NISTC_DIO_OUT_PARALLEL_MASK;
		devpriv->dio_output |= NISTC_DIO_OUT_PARALLEL(s->state);
		ni_stc_writew(dev, devpriv->dio_output, NISTC_DIO_OUT_REG);
	}

	data[1] = ni_stc_readw(dev, NISTC_DIO_IN_REG);

	return insn->n;
}