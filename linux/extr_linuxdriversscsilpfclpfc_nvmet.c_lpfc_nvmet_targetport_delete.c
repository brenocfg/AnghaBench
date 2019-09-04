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
struct nvmet_fc_target_port {struct lpfc_nvmet_tgtport* private; } ;
struct lpfc_nvmet_tgtport {int /*<<< orphan*/  tport_unreg_cmp; TYPE_1__* phba; } ;
struct TYPE_2__ {scalar_t__ targetport; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_nvmet_targetport_delete(struct nvmet_fc_target_port *targetport)
{
	struct lpfc_nvmet_tgtport *tport = targetport->private;

	/* release any threads waiting for the unreg to complete */
	if (tport->phba->targetport)
		complete(tport->tport_unreg_cmp);
}