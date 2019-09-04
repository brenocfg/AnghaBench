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
struct comedi_device {scalar_t__ iobase; } ;
struct comedi_cmd {int chanlist_len; int /*<<< orphan*/ * chanlist; } ;

/* Variables and functions */
 unsigned int AREF_DIFF ; 
 unsigned int CR_AREF (int /*<<< orphan*/ ) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ ME4000_AI_CHANNEL_LIST_REG ; 
 unsigned int ME4000_AI_LIST_INPUT_DIFFERENTIAL ; 
 unsigned int ME4000_AI_LIST_LAST_ENTRY ; 
 unsigned int ME4000_AI_LIST_RANGE (unsigned int) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

__attribute__((used)) static void me4000_ai_write_chanlist(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     struct comedi_cmd *cmd)
{
	int i;

	for (i = 0; i < cmd->chanlist_len; i++) {
		unsigned int chan = CR_CHAN(cmd->chanlist[i]);
		unsigned int range = CR_RANGE(cmd->chanlist[i]);
		unsigned int aref = CR_AREF(cmd->chanlist[i]);
		unsigned int entry;

		entry = chan | ME4000_AI_LIST_RANGE(range);

		if (aref == AREF_DIFF)
			entry |= ME4000_AI_LIST_INPUT_DIFFERENTIAL;

		if (i == (cmd->chanlist_len - 1))
			entry |= ME4000_AI_LIST_LAST_ENTRY;

		outl(entry, dev->iobase + ME4000_AI_CHANNEL_LIST_REG);
	}
}