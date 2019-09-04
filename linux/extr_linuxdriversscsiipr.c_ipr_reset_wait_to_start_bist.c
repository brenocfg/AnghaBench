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
struct ipr_ioa_cfg {int dummy; } ;
struct TYPE_2__ {scalar_t__ time_left; } ;
struct ipr_cmnd {int /*<<< orphan*/  job_step; TYPE_1__ u; struct ipr_ioa_cfg* ioa_cfg; } ;

/* Variables and functions */
 scalar_t__ IPR_CHECK_FOR_RESET_TIMEOUT ; 
 int IPR_RC_JOB_CONTINUE ; 
 int IPR_RC_JOB_RETURN ; 
 int /*<<< orphan*/  ipr_reset_allowed (struct ipr_ioa_cfg*) ; 
 int /*<<< orphan*/  ipr_reset_block_config_access ; 
 int /*<<< orphan*/  ipr_reset_start_timer (struct ipr_cmnd*,scalar_t__) ; 

__attribute__((used)) static int ipr_reset_wait_to_start_bist(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	int rc = IPR_RC_JOB_RETURN;

	if (!ipr_reset_allowed(ioa_cfg) && ipr_cmd->u.time_left) {
		ipr_cmd->u.time_left -= IPR_CHECK_FOR_RESET_TIMEOUT;
		ipr_reset_start_timer(ipr_cmd, IPR_CHECK_FOR_RESET_TIMEOUT);
	} else {
		ipr_cmd->job_step = ipr_reset_block_config_access;
		rc = IPR_RC_JOB_CONTINUE;
	}

	return rc;
}