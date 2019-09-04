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
struct tcm_loop_tpg {int /*<<< orphan*/  tl_transport_status; } ;
struct tcm_loop_hba {struct tcm_loop_tpg* tl_hba_tpgs; } ;
struct scsi_cmnd {TYPE_1__* device; } ;
struct TYPE_2__ {size_t id; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int FAILED ; 
 int SUCCESS ; 
 int /*<<< orphan*/  TCM_TRANSPORT_ONLINE ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcm_loop_target_reset(struct scsi_cmnd *sc)
{
	struct tcm_loop_hba *tl_hba;
	struct tcm_loop_tpg *tl_tpg;

	/*
	 * Locate the tcm_loop_hba_t pointer
	 */
	tl_hba = *(struct tcm_loop_hba **)shost_priv(sc->device->host);
	if (!tl_hba) {
		pr_err("Unable to perform device reset without active I_T Nexus\n");
		return FAILED;
	}
	/*
	 * Locate the tl_tpg pointer from TargetID in sc->device->id
	 */
	tl_tpg = &tl_hba->tl_hba_tpgs[sc->device->id];
	if (tl_tpg) {
		tl_tpg->tl_transport_status = TCM_TRANSPORT_ONLINE;
		return SUCCESS;
	}
	return FAILED;
}