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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct comedi_subdevice* read_subdev; struct ni_private* private; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned short*) ; 
 int /*<<< orphan*/  NI611X_AI_FIFO_DATA_REG ; 
 int /*<<< orphan*/  NI6143_AI_FIFO_CTRL_REG ; 
 int /*<<< orphan*/  NI6143_AI_FIFO_DATA_REG ; 
 int /*<<< orphan*/  NI6143_AI_FIFO_STATUS_REG ; 
 unsigned short NISTC_AI_STATUS1_FIFO_E ; 
 int /*<<< orphan*/  NISTC_AI_STATUS1_REG ; 
 int /*<<< orphan*/  NI_E_AI_FIFO_DATA_REG ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned short*,int) ; 
 int ni_readl (struct comedi_device*,int /*<<< orphan*/ ) ; 
 unsigned short ni_readw (struct comedi_device*,int /*<<< orphan*/ ) ; 
 unsigned short ni_stc_readw (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_writel (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_handle_fifo_dregs(struct comedi_device *dev)
{
	struct ni_private *devpriv = dev->private;
	struct comedi_subdevice *s = dev->read_subdev;
	unsigned int dl;
	unsigned short data;
	int i;

	if (devpriv->is_611x) {
		while ((ni_stc_readw(dev, NISTC_AI_STATUS1_REG) &
			NISTC_AI_STATUS1_FIFO_E) == 0) {
			dl = ni_readl(dev, NI611X_AI_FIFO_DATA_REG);

			/* This may get the hi/lo data in the wrong order */
			data = dl >> 16;
			comedi_buf_write_samples(s, &data, 1);
			data = dl & 0xffff;
			comedi_buf_write_samples(s, &data, 1);
		}
	} else if (devpriv->is_6143) {
		i = 0;
		while (ni_readl(dev, NI6143_AI_FIFO_STATUS_REG) & 0x04) {
			dl = ni_readl(dev, NI6143_AI_FIFO_DATA_REG);

			/* This may get the hi/lo data in the wrong order */
			data = dl >> 16;
			comedi_buf_write_samples(s, &data, 1);
			data = dl & 0xffff;
			comedi_buf_write_samples(s, &data, 1);
			i += 2;
		}
		/*  Check if stranded sample is present */
		if (ni_readl(dev, NI6143_AI_FIFO_STATUS_REG) & 0x01) {
			/* Get stranded sample into FIFO */
			ni_writel(dev, 0x01, NI6143_AI_FIFO_CTRL_REG);
			dl = ni_readl(dev, NI6143_AI_FIFO_DATA_REG);
			data = (dl >> 16) & 0xffff;
			comedi_buf_write_samples(s, &data, 1);
		}

	} else {
		unsigned short fe;	/* fifo empty */

		fe = ni_stc_readw(dev, NISTC_AI_STATUS1_REG) &
		     NISTC_AI_STATUS1_FIFO_E;
		while (fe == 0) {
			for (i = 0;
			     i < ARRAY_SIZE(devpriv->ai_fifo_buffer); i++) {
				fe = ni_stc_readw(dev, NISTC_AI_STATUS1_REG) &
				     NISTC_AI_STATUS1_FIFO_E;
				if (fe)
					break;
				devpriv->ai_fifo_buffer[i] =
				    ni_readw(dev, NI_E_AI_FIFO_DATA_REG);
			}
			comedi_buf_write_samples(s, devpriv->ai_fifo_buffer, i);
		}
	}
}