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
struct task_status_struct {int buf_valid_size; int /*<<< orphan*/  resp; int /*<<< orphan*/  stat; int /*<<< orphan*/ * buf; } ;
struct sas_task {struct task_status_struct task_status; } ;
struct dev_to_host_fis {int /*<<< orphan*/  status; } ;
struct ata_task_resp {int frame_len; int /*<<< orphan*/  ending_fis; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
 int /*<<< orphan*/  SAS_PROTO_RESPONSE ; 
 int /*<<< orphan*/  SAS_TASK_COMPLETE ; 
 scalar_t__ ac_err_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct dev_to_host_fis*,int) ; 

__attribute__((used)) static void isci_process_stp_response(struct sas_task *task, struct dev_to_host_fis *fis)
{
	struct task_status_struct *ts = &task->task_status;
	struct ata_task_resp *resp = (void *)&ts->buf[0];

	resp->frame_len = sizeof(*fis);
	memcpy(resp->ending_fis, fis, sizeof(*fis));
	ts->buf_valid_size = sizeof(*resp);

	/* If an error is flagged let libata decode the fis */
	if (ac_err_mask(fis->status))
		ts->stat = SAS_PROTO_RESPONSE;
	else
		ts->stat = SAM_STAT_GOOD;

	ts->resp = SAS_TASK_COMPLETE;
}