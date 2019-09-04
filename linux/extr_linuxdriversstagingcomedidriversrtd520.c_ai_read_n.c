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
struct rtd_private {scalar_t__ ai_count; scalar_t__ las1; } ;
struct comedi_subdevice {unsigned short maxdata; struct comedi_async* async; } ;
struct comedi_device {struct rtd_private* private; } ;
struct comedi_cmd {int /*<<< orphan*/ * chanlist; } ;
struct comedi_async {size_t cur_chan; struct comedi_cmd cmd; } ;

/* Variables and functions */
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ LAS1_ADC_FIFO ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned short*,int) ; 
 unsigned short comedi_offset_munge (struct comedi_subdevice*,unsigned short) ; 
 scalar_t__ comedi_range_is_bipolar (struct comedi_subdevice*,unsigned int) ; 
 unsigned short readw (scalar_t__) ; 

__attribute__((used)) static int ai_read_n(struct comedi_device *dev, struct comedi_subdevice *s,
		     int count)
{
	struct rtd_private *devpriv = dev->private;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	int ii;

	for (ii = 0; ii < count; ii++) {
		unsigned int range = CR_RANGE(cmd->chanlist[async->cur_chan]);
		unsigned short d;

		if (devpriv->ai_count == 0) {	/* done */
			d = readw(devpriv->las1 + LAS1_ADC_FIFO);
			continue;
		}

		d = readw(devpriv->las1 + LAS1_ADC_FIFO);
		d >>= 3;	/* low 3 bits are marker lines */

		/* convert bipolar data to comedi unsigned data */
		if (comedi_range_is_bipolar(s, range))
			d = comedi_offset_munge(s, d);
		d &= s->maxdata;

		if (!comedi_buf_write_samples(s, &d, 1))
			return -1;

		if (devpriv->ai_count > 0)	/* < 0, means read forever */
			devpriv->ai_count--;
	}
	return 0;
}