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
struct das1800_private {int /*<<< orphan*/  fifo_buf; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ iobase; struct das1800_private* private; } ;

/* Variables and functions */
 scalar_t__ DAS1800_FIFO ; 
 int FIFO_SIZE ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int comedi_nsamples_left (struct comedi_subdevice*,int) ; 
 int /*<<< orphan*/  insw (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void das1800_handle_fifo_half_full(struct comedi_device *dev,
					  struct comedi_subdevice *s)
{
	struct das1800_private *devpriv = dev->private;
	unsigned int nsamples = comedi_nsamples_left(s, FIFO_SIZE / 2);

	insw(dev->iobase + DAS1800_FIFO, devpriv->fifo_buf, nsamples);
	comedi_buf_write_samples(s, devpriv->fifo_buf, nsamples);
}