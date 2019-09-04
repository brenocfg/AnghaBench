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
struct ni_private {unsigned int* ai_offset; scalar_t__ is_m_series; scalar_t__ is_6143; scalar_t__ is_611x; } ;
struct comedi_subdevice {unsigned int maxdata; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct ni_private* private; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  NI611X_AI_FIFO_DATA_REG ; 
 int /*<<< orphan*/  NI6143_AI_FIFO_CTRL_REG ; 
 int /*<<< orphan*/  NI6143_AI_FIFO_DATA_REG ; 
 int /*<<< orphan*/  NI6143_AI_FIFO_STATUS_REG ; 
 int /*<<< orphan*/  NISTC_AI_CMD1_CONVERT_PULSE ; 
 int /*<<< orphan*/  NISTC_AI_CMD1_REG ; 
 int NISTC_AI_STATUS1_FIFO_E ; 
 int /*<<< orphan*/  NISTC_AI_STATUS1_REG ; 
 int /*<<< orphan*/  NI_E_AI_FIFO_DATA_REG ; 
 int /*<<< orphan*/  NI_E_STATUS_REG ; 
 int /*<<< orphan*/  NI_M_AI_FIFO_DATA_REG ; 
 int NI_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ni_clear_ai_fifo (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_load_channelgain_list (struct comedi_device*,struct comedi_subdevice*,int,int /*<<< orphan*/ *) ; 
 int ni_readb (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int ni_readl (struct comedi_device*,int /*<<< orphan*/ ) ; 
 unsigned int ni_readw (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int ni_stc_readw (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_writel (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int num_adc_stages_611x ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ni_ai_insn_read(struct comedi_device *dev,
			   struct comedi_subdevice *s,
			   struct comedi_insn *insn,
			   unsigned int *data)
{
	struct ni_private *devpriv = dev->private;
	unsigned int mask = s->maxdata;
	int i, n;
	unsigned int signbits;
	unsigned int d;

	ni_load_channelgain_list(dev, s, 1, &insn->chanspec);

	ni_clear_ai_fifo(dev);

	signbits = devpriv->ai_offset[0];
	if (devpriv->is_611x) {
		for (n = 0; n < num_adc_stages_611x; n++) {
			ni_stc_writew(dev, NISTC_AI_CMD1_CONVERT_PULSE,
				      NISTC_AI_CMD1_REG);
			udelay(1);
		}
		for (n = 0; n < insn->n; n++) {
			ni_stc_writew(dev, NISTC_AI_CMD1_CONVERT_PULSE,
				      NISTC_AI_CMD1_REG);
			/* The 611x has screwy 32-bit FIFOs. */
			d = 0;
			for (i = 0; i < NI_TIMEOUT; i++) {
				if (ni_readb(dev, NI_E_STATUS_REG) & 0x80) {
					d = ni_readl(dev,
						     NI611X_AI_FIFO_DATA_REG);
					d >>= 16;
					d &= 0xffff;
					break;
				}
				if (!(ni_stc_readw(dev, NISTC_AI_STATUS1_REG) &
				      NISTC_AI_STATUS1_FIFO_E)) {
					d = ni_readl(dev,
						     NI611X_AI_FIFO_DATA_REG);
					d &= 0xffff;
					break;
				}
			}
			if (i == NI_TIMEOUT) {
				dev_err(dev->class_dev, "timeout\n");
				return -ETIME;
			}
			d += signbits;
			data[n] = d & 0xffff;
		}
	} else if (devpriv->is_6143) {
		for (n = 0; n < insn->n; n++) {
			ni_stc_writew(dev, NISTC_AI_CMD1_CONVERT_PULSE,
				      NISTC_AI_CMD1_REG);

			/*
			 * The 6143 has 32-bit FIFOs. You need to strobe a
			 * bit to move a single 16bit stranded sample into
			 * the FIFO.
			 */
			d = 0;
			for (i = 0; i < NI_TIMEOUT; i++) {
				if (ni_readl(dev, NI6143_AI_FIFO_STATUS_REG) &
				    0x01) {
					/* Get stranded sample into FIFO */
					ni_writel(dev, 0x01,
						  NI6143_AI_FIFO_CTRL_REG);
					d = ni_readl(dev,
						     NI6143_AI_FIFO_DATA_REG);
					break;
				}
			}
			if (i == NI_TIMEOUT) {
				dev_err(dev->class_dev, "timeout\n");
				return -ETIME;
			}
			data[n] = (((d >> 16) & 0xFFFF) + signbits) & 0xFFFF;
		}
	} else {
		for (n = 0; n < insn->n; n++) {
			ni_stc_writew(dev, NISTC_AI_CMD1_CONVERT_PULSE,
				      NISTC_AI_CMD1_REG);
			for (i = 0; i < NI_TIMEOUT; i++) {
				if (!(ni_stc_readw(dev, NISTC_AI_STATUS1_REG) &
				      NISTC_AI_STATUS1_FIFO_E))
					break;
			}
			if (i == NI_TIMEOUT) {
				dev_err(dev->class_dev, "timeout\n");
				return -ETIME;
			}
			if (devpriv->is_m_series) {
				d = ni_readl(dev, NI_M_AI_FIFO_DATA_REG);
				d &= mask;
				data[n] = d;
			} else {
				d = ni_readw(dev, NI_E_AI_FIFO_DATA_REG);
				d += signbits;
				data[n] = d & 0xffff;
			}
		}
	}
	return insn->n;
}