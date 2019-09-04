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
struct ni_private {unsigned short* ai_fifo_buffer; scalar_t__ is_6143; scalar_t__ is_611x; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct ni_private* private; } ;
struct comedi_async {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned short*) ; 
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 int /*<<< orphan*/  NI611X_AI_FIFO_DATA_REG ; 
 int /*<<< orphan*/  NI6143_AI_FIFO_CTRL_REG ; 
 int /*<<< orphan*/  NI6143_AI_FIFO_DATA_REG ; 
 int /*<<< orphan*/  NI_E_AI_FIFO_DATA_REG ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned short*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int ni_readl (struct comedi_device*,int /*<<< orphan*/ ) ; 
 unsigned short ni_readw (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_writel (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_ai_fifo_read(struct comedi_device *dev,
			    struct comedi_subdevice *s, int n)
{
	struct ni_private *devpriv = dev->private;
	struct comedi_async *async = s->async;
	unsigned int dl;
	unsigned short data;
	int i;

	if (devpriv->is_611x) {
		for (i = 0; i < n / 2; i++) {
			dl = ni_readl(dev, NI611X_AI_FIFO_DATA_REG);
			/* This may get the hi/lo data in the wrong order */
			data = (dl >> 16) & 0xffff;
			comedi_buf_write_samples(s, &data, 1);
			data = dl & 0xffff;
			comedi_buf_write_samples(s, &data, 1);
		}
		/* Check if there's a single sample stuck in the FIFO */
		if (n % 2) {
			dl = ni_readl(dev, NI611X_AI_FIFO_DATA_REG);
			data = dl & 0xffff;
			comedi_buf_write_samples(s, &data, 1);
		}
	} else if (devpriv->is_6143) {
		/*
		 * This just reads the FIFO assuming the data is present,
		 * no checks on the FIFO status are performed.
		 */
		for (i = 0; i < n / 2; i++) {
			dl = ni_readl(dev, NI6143_AI_FIFO_DATA_REG);

			data = (dl >> 16) & 0xffff;
			comedi_buf_write_samples(s, &data, 1);
			data = dl & 0xffff;
			comedi_buf_write_samples(s, &data, 1);
		}
		if (n % 2) {
			/* Assume there is a single sample stuck in the FIFO */
			/* Get stranded sample into FIFO */
			ni_writel(dev, 0x01, NI6143_AI_FIFO_CTRL_REG);
			dl = ni_readl(dev, NI6143_AI_FIFO_DATA_REG);
			data = (dl >> 16) & 0xffff;
			comedi_buf_write_samples(s, &data, 1);
		}
	} else {
		if (n > ARRAY_SIZE(devpriv->ai_fifo_buffer)) {
			dev_err(dev->class_dev,
				"bug! ai_fifo_buffer too small\n");
			async->events |= COMEDI_CB_ERROR;
			return;
		}
		for (i = 0; i < n; i++) {
			devpriv->ai_fifo_buffer[i] =
			    ni_readw(dev, NI_E_AI_FIFO_DATA_REG);
		}
		comedi_buf_write_samples(s, devpriv->ai_fifo_buffer, n);
	}
}