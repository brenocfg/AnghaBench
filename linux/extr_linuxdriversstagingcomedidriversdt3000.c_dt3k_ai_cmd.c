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
struct comedi_device {scalar_t__ mmio; } ;
struct comedi_cmd {int chanlist_len; int scan_end_arg; scalar_t__ convert_src; scalar_t__ scan_begin_src; int /*<<< orphan*/  flags; int /*<<< orphan*/  scan_begin_arg; int /*<<< orphan*/  convert_arg; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_2__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 unsigned int AREF_DIFF ; 
 unsigned int CR_AREF (int /*<<< orphan*/ ) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DPR_ADC_BUFFER ; 
 int DPR_AI_FIFO_DEPTH ; 
 int /*<<< orphan*/  DPR_CMD_CONFIG ; 
 int /*<<< orphan*/  DPR_CMD_START ; 
 int DPR_INTR_ADFULL ; 
 int DPR_INTR_ADHWERR ; 
 int DPR_INTR_ADSWERR ; 
 scalar_t__ DPR_INT_MASK ; 
 int DPR_PARAM5_AD_TRIG_INT_RETRIG ; 
 int DPR_PARAM6_AD_DIFF ; 
 scalar_t__ DPR_PARAMS (int) ; 
 scalar_t__ DPR_SUBSYS ; 
 int DPR_SUBSYS_AI ; 
 scalar_t__ TRIG_TIMER ; 
 scalar_t__ debug_n_ints ; 
 unsigned int dt3k_ns_to_timer (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt3k_send_cmd (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int dt3k_ai_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct comedi_cmd *cmd = &s->async->cmd;
	int i;
	unsigned int chan, range, aref;
	unsigned int divider;
	unsigned int tscandiv;

	for (i = 0; i < cmd->chanlist_len; i++) {
		chan = CR_CHAN(cmd->chanlist[i]);
		range = CR_RANGE(cmd->chanlist[i]);

		writew((range << 6) | chan, dev->mmio + DPR_ADC_BUFFER + i);
	}
	aref = CR_AREF(cmd->chanlist[0]);

	writew(cmd->scan_end_arg, dev->mmio + DPR_PARAMS(0));

	if (cmd->convert_src == TRIG_TIMER) {
		divider = dt3k_ns_to_timer(50, &cmd->convert_arg, cmd->flags);
		writew((divider >> 16), dev->mmio + DPR_PARAMS(1));
		writew((divider & 0xffff), dev->mmio + DPR_PARAMS(2));
	}

	if (cmd->scan_begin_src == TRIG_TIMER) {
		tscandiv = dt3k_ns_to_timer(100, &cmd->scan_begin_arg,
					    cmd->flags);
		writew((tscandiv >> 16), dev->mmio + DPR_PARAMS(3));
		writew((tscandiv & 0xffff), dev->mmio + DPR_PARAMS(4));
	}

	writew(DPR_PARAM5_AD_TRIG_INT_RETRIG, dev->mmio + DPR_PARAMS(5));
	writew((aref == AREF_DIFF) ? DPR_PARAM6_AD_DIFF : 0,
	       dev->mmio + DPR_PARAMS(6));

	writew(DPR_AI_FIFO_DEPTH / 2, dev->mmio + DPR_PARAMS(7));

	writew(DPR_SUBSYS_AI, dev->mmio + DPR_SUBSYS);
	dt3k_send_cmd(dev, DPR_CMD_CONFIG);

	writew(DPR_INTR_ADFULL | DPR_INTR_ADSWERR | DPR_INTR_ADHWERR,
	       dev->mmio + DPR_INT_MASK);

	debug_n_ints = 0;

	writew(DPR_SUBSYS_AI, dev->mmio + DPR_SUBSYS);
	dt3k_send_cmd(dev, DPR_CMD_START);

	return 0;
}