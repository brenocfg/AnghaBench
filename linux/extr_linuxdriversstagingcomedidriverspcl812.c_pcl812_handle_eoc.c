#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; } ;
struct comedi_cmd {scalar_t__* chanlist; } ;
struct TYPE_2__ {unsigned int cur_chan; int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned short*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pcl812_ai_eoc (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned short pcl812_ai_get_sample (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pcl812_ai_next_chan (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pcl812_ai_set_chan_range (struct comedi_device*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcl812_handle_eoc(struct comedi_device *dev,
			      struct comedi_subdevice *s)
{
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int chan = s->async->cur_chan;
	unsigned int next_chan;
	unsigned short val;

	if (pcl812_ai_eoc(dev, s, NULL, 0)) {
		dev_dbg(dev->class_dev, "A/D cmd IRQ without DRDY!\n");
		s->async->events |= COMEDI_CB_ERROR;
		return;
	}

	val = pcl812_ai_get_sample(dev, s);
	comedi_buf_write_samples(s, &val, 1);

	/* Set up next channel. Added by abbotti 2010-01-20, but untested. */
	next_chan = s->async->cur_chan;
	if (cmd->chanlist[chan] != cmd->chanlist[next_chan])
		pcl812_ai_set_chan_range(dev, cmd->chanlist[next_chan], 0);

	pcl812_ai_next_chan(dev, s);
}