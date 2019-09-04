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
struct ctlr_info {int dummy; } ;
struct CommandList {TYPE_1__* err_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  CommandStatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CTLR_LOCKUP ; 
 int IO_OK ; 
 int hpsa_scsi_do_simple_cmd_core (struct ctlr_info*,struct CommandList*,int,unsigned long) ; 
 int /*<<< orphan*/  lockup_detected (struct ctlr_info*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpsa_scsi_do_simple_cmd(struct ctlr_info *h, struct CommandList *c,
				   int reply_queue, unsigned long timeout_msecs)
{
	if (unlikely(lockup_detected(h))) {
		c->err_info->CommandStatus = CMD_CTLR_LOCKUP;
		return IO_OK;
	}
	return hpsa_scsi_do_simple_cmd_core(h, c, reply_queue, timeout_msecs);
}