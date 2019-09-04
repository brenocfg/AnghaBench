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
struct comedi_subdevice {unsigned short* readback; struct comedi_async* async; } ;
struct comedi_device {int dummy; } ;
struct comedi_cmd {scalar_t__ stop_src; scalar_t__ stop_arg; int chanlist_len; int /*<<< orphan*/ * chanlist; } ;
struct comedi_async {scalar_t__ scans_done; int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_OVERFLOW ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  comedi_buf_read_samples (struct comedi_subdevice*,unsigned short*,int) ; 
 int /*<<< orphan*/  pci230_ao_write_nofifo (struct comedi_device*,unsigned short,unsigned int) ; 

__attribute__((used)) static void pci230_handle_ao_nofifo(struct comedi_device *dev,
				    struct comedi_subdevice *s)
{
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned short data;
	int i;

	if (cmd->stop_src == TRIG_COUNT && async->scans_done >= cmd->stop_arg)
		return;

	for (i = 0; i < cmd->chanlist_len; i++) {
		unsigned int chan = CR_CHAN(cmd->chanlist[i]);

		if (!comedi_buf_read_samples(s, &data, 1)) {
			async->events |= COMEDI_CB_OVERFLOW;
			return;
		}
		pci230_ao_write_nofifo(dev, data, chan);
		s->readback[chan] = data;
	}

	if (cmd->stop_src == TRIG_COUNT && async->scans_done >= cmd->stop_arg)
		async->events |= COMEDI_CB_EOA;
}