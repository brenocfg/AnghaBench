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
struct ni_private {int serial_interval_ns; int /*<<< orphan*/  dio_control; int /*<<< orphan*/  dio_output; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  NISTC_DIO_CTRL_REG ; 
 int /*<<< orphan*/  NISTC_DIO_IN_REG ; 
 int /*<<< orphan*/  NISTC_DIO_OUT_REG ; 
 int /*<<< orphan*/  NISTC_DIO_SDCLK ; 
 int NISTC_DIO_SDIN ; 
 int /*<<< orphan*/  NISTC_DIO_SDOUT ; 
 int ni_stc_readw (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ni_serial_sw_readwrite8(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   unsigned char data_out,
				   unsigned char *data_in)
{
	struct ni_private *devpriv = dev->private;
	unsigned char mask, input = 0;

	/* Wait for one bit before transfer */
	udelay((devpriv->serial_interval_ns + 999) / 1000);

	for (mask = 0x80; mask; mask >>= 1) {
		/*
		 * Output current bit; note that we cannot touch s->state
		 * because it is a per-subdevice field, and serial is
		 * a separate subdevice from DIO.
		 */
		devpriv->dio_output &= ~NISTC_DIO_SDOUT;
		if (data_out & mask)
			devpriv->dio_output |= NISTC_DIO_SDOUT;
		ni_stc_writew(dev, devpriv->dio_output, NISTC_DIO_OUT_REG);

		/*
		 * Assert SDCLK (active low, inverted), wait for half of
		 * the delay, deassert SDCLK, and wait for the other half.
		 */
		devpriv->dio_control |= NISTC_DIO_SDCLK;
		ni_stc_writew(dev, devpriv->dio_control, NISTC_DIO_CTRL_REG);

		udelay((devpriv->serial_interval_ns + 999) / 2000);

		devpriv->dio_control &= ~NISTC_DIO_SDCLK;
		ni_stc_writew(dev, devpriv->dio_control, NISTC_DIO_CTRL_REG);

		udelay((devpriv->serial_interval_ns + 999) / 2000);

		/* Input current bit */
		if (ni_stc_readw(dev, NISTC_DIO_IN_REG) & NISTC_DIO_SDIN)
			input |= mask;
	}

	if (data_in)
		*data_in = input;

	return 0;
}