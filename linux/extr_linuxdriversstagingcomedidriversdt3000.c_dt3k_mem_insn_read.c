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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPR_CMD_READCODE ; 
 scalar_t__ DPR_PARAMS (int) ; 
 scalar_t__ DPR_SUBSYS ; 
 int DPR_SUBSYS_MEM ; 
 int /*<<< orphan*/  dt3k_send_cmd (struct comedi_device*,int /*<<< orphan*/ ) ; 
 unsigned int readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int dt3k_mem_insn_read(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn,
			      unsigned int *data)
{
	unsigned int addr = CR_CHAN(insn->chanspec);
	int i;

	for (i = 0; i < insn->n; i++) {
		writew(DPR_SUBSYS_MEM, dev->mmio + DPR_SUBSYS);
		writew(addr, dev->mmio + DPR_PARAMS(0));
		writew(1, dev->mmio + DPR_PARAMS(1));

		dt3k_send_cmd(dev, DPR_CMD_READCODE);

		data[i] = readw(dev->mmio + DPR_PARAMS(2));
	}

	return i;
}