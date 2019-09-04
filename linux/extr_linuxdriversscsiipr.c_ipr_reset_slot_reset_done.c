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
struct ipr_cmnd {int /*<<< orphan*/  job_step; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int IPR_RC_JOB_RETURN ; 
 int /*<<< orphan*/  IPR_WAIT_FOR_BIST_TIMEOUT ; 
 int /*<<< orphan*/  LEAVE ; 
 int /*<<< orphan*/  ipr_reset_bist_done ; 
 int /*<<< orphan*/  ipr_reset_start_timer (struct ipr_cmnd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipr_reset_slot_reset_done(struct ipr_cmnd *ipr_cmd)
{
	ENTER;
	ipr_cmd->job_step = ipr_reset_bist_done;
	ipr_reset_start_timer(ipr_cmd, IPR_WAIT_FOR_BIST_TIMEOUT);
	LEAVE;
	return IPR_RC_JOB_RETURN;
}