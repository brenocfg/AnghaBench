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
struct comedi_device {int dummy; } ;
struct comedi_cmd {unsigned int chanlist_len; scalar_t__ stop_src; scalar_t__ stop_arg; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_2__ {scalar_t__ scans_done; int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned short*,int) ; 

__attribute__((used)) static void dio200_read_scan_intr(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  unsigned int triggered)
{
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned short val;
	unsigned int n, ch;

	val = 0;
	for (n = 0; n < cmd->chanlist_len; n++) {
		ch = CR_CHAN(cmd->chanlist[n]);
		if (triggered & (1U << ch))
			val |= (1U << n);
	}

	comedi_buf_write_samples(s, &val, 1);

	if (cmd->stop_src == TRIG_COUNT &&
	    s->async->scans_done >= cmd->stop_arg)
		s->async->events |= COMEDI_CB_EOA;
}