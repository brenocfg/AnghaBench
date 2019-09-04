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
struct scsi_eh_save {int /*<<< orphan*/  eh_eflags; int /*<<< orphan*/  prot_op; int /*<<< orphan*/  underflow; int /*<<< orphan*/  result; int /*<<< orphan*/  next_rq; int /*<<< orphan*/  sdb; int /*<<< orphan*/  data_direction; int /*<<< orphan*/  cmnd; int /*<<< orphan*/  cmd_len; } ;
struct scsi_cmnd {int /*<<< orphan*/  eh_eflags; int /*<<< orphan*/  prot_op; int /*<<< orphan*/  underflow; int /*<<< orphan*/  result; TYPE_1__* request; int /*<<< orphan*/  sdb; int /*<<< orphan*/  sc_data_direction; int /*<<< orphan*/  cmnd; int /*<<< orphan*/  cmd_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  next_rq; } ;

/* Variables and functions */

void scsi_eh_restore_cmnd(struct scsi_cmnd* scmd, struct scsi_eh_save *ses)
{
	/*
	 * Restore original data
	 */
	scmd->cmd_len = ses->cmd_len;
	scmd->cmnd = ses->cmnd;
	scmd->sc_data_direction = ses->data_direction;
	scmd->sdb = ses->sdb;
	scmd->request->next_rq = ses->next_rq;
	scmd->result = ses->result;
	scmd->underflow = ses->underflow;
	scmd->prot_op = ses->prot_op;
	scmd->eh_eflags = ses->eh_eflags;
}