#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  reset_action; int /*<<< orphan*/  reset_type; } ;
union pqi_reset_register {scalar_t__ all_bits; TYPE_1__ bits; } ;
struct pqi_ctrl_info {TYPE_3__* pci_dev; TYPE_2__* pqi_registers; scalar_t__ pqi_reset_quiesce_supported; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  device_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  PQI_RESET_ACTION_RESET ; 
 int /*<<< orphan*/  PQI_RESET_TYPE_HARD_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int pqi_wait_for_pqi_reset_completion (struct pqi_ctrl_info*) ; 
 int sis_pqi_reset_quiesce (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pqi_reset(struct pqi_ctrl_info *ctrl_info)
{
	int rc;
	union pqi_reset_register reset_reg;

	if (ctrl_info->pqi_reset_quiesce_supported) {
		rc = sis_pqi_reset_quiesce(ctrl_info);
		if (rc) {
			dev_err(&ctrl_info->pci_dev->dev,
				"PQI reset failed during quiesce with error %d\n",
				rc);
			return rc;
		}
	}

	reset_reg.all_bits = 0;
	reset_reg.bits.reset_type = PQI_RESET_TYPE_HARD_RESET;
	reset_reg.bits.reset_action = PQI_RESET_ACTION_RESET;

	writel(reset_reg.all_bits, &ctrl_info->pqi_registers->device_reset);

	rc = pqi_wait_for_pqi_reset_completion(ctrl_info);
	if (rc)
		dev_err(&ctrl_info->pci_dev->dev,
			"PQI reset failed with error %d\n", rc);

	return rc;
}