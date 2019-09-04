#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct qla_hw_data {int /*<<< orphan*/  chip_revision; TYPE_4__* pdev; } ;
struct TYPE_6__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;
struct TYPE_7__ {int /*<<< orphan*/  revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_set_master (TYPE_4__*) ; 
 int pci_set_mwi (TYPE_4__*) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_1__*,int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg_init ; 

int
qla82xx_pci_config(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;
	int ret;

	pci_set_master(ha->pdev);
	ret = pci_set_mwi(ha->pdev);
	ha->chip_revision = ha->pdev->revision;
	ql_dbg(ql_dbg_init, vha, 0x0043,
	    "Chip revision:%d; pci_set_mwi() returned %d.\n",
	    ha->chip_revision, ret);
	return 0;
}