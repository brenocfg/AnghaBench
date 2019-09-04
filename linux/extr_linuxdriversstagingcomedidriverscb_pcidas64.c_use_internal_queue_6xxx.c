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
struct comedi_cmd {int chanlist_len; int /*<<< orphan*/ * chanlist; } ;

/* Variables and functions */
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 scalar_t__ CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ CR_RANGE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int use_internal_queue_6xxx(const struct comedi_cmd *cmd)
{
	int i;

	for (i = 0; i + 1 < cmd->chanlist_len; i++) {
		if (CR_CHAN(cmd->chanlist[i + 1]) !=
		    CR_CHAN(cmd->chanlist[i]) + 1)
			return 0;
		if (CR_RANGE(cmd->chanlist[i + 1]) !=
		    CR_RANGE(cmd->chanlist[i]))
			return 0;
		if (CR_AREF(cmd->chanlist[i + 1]) != CR_AREF(cmd->chanlist[i]))
			return 0;
	}
	return 1;
}