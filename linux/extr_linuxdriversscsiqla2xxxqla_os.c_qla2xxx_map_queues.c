#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int /*<<< orphan*/  tag_set; scalar_t__ hostdata; } ;
struct TYPE_3__ {TYPE_2__* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;
struct TYPE_4__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ USER_CTRL_IRQ (TYPE_2__*) ; 
 int blk_mq_map_queues (int /*<<< orphan*/ *) ; 
 int blk_mq_pci_map_queues (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qla2xxx_map_queues(struct Scsi_Host *shost)
{
	int rc;
	scsi_qla_host_t *vha = (scsi_qla_host_t *)shost->hostdata;

	if (USER_CTRL_IRQ(vha->hw))
		rc = blk_mq_map_queues(&shost->tag_set);
	else
		rc = blk_mq_pci_map_queues(&shost->tag_set, vha->hw->pdev, 0);
	return rc;
}