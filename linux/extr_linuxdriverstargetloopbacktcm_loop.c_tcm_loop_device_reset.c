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
struct tcm_loop_tpg {int dummy; } ;
struct tcm_loop_hba {struct tcm_loop_tpg* tl_hba_tpgs; } ;
struct scsi_cmnd {TYPE_1__* device; } ;
struct TYPE_2__ {size_t id; int /*<<< orphan*/  lun; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int FAILED ; 
 int SUCCESS ; 
 int TMR_FUNCTION_COMPLETE ; 
 int /*<<< orphan*/  TMR_LUN_RESET ; 
 scalar_t__ shost_priv (int /*<<< orphan*/ ) ; 
 int tcm_loop_issue_tmr (struct tcm_loop_tpg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcm_loop_device_reset(struct scsi_cmnd *sc)
{
	struct tcm_loop_hba *tl_hba;
	struct tcm_loop_tpg *tl_tpg;
	int ret = FAILED;

	/*
	 * Locate the tcm_loop_hba_t pointer
	 */
	tl_hba = *(struct tcm_loop_hba **)shost_priv(sc->device->host);
	tl_tpg = &tl_hba->tl_hba_tpgs[sc->device->id];

	ret = tcm_loop_issue_tmr(tl_tpg, sc->device->lun,
				 0, TMR_LUN_RESET);
	return (ret == TMR_FUNCTION_COMPLETE) ? SUCCESS : FAILED;
}