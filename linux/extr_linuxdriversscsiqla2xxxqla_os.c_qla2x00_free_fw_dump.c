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
struct qla_hw_data {scalar_t__ fw_dump_template_len; int /*<<< orphan*/ * fw_dump_template; scalar_t__ fw_dump_len; int /*<<< orphan*/ * fw_dump; scalar_t__ fw_dump_reading; scalar_t__ fw_dump_cap_flags; scalar_t__ fw_dumped; scalar_t__ eft_dma; int /*<<< orphan*/ * eft; scalar_t__ fce_dma; int /*<<< orphan*/ * fce; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFT_SIZE ; 
 int /*<<< orphan*/  FCE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qla2x00_free_fw_dump(struct qla_hw_data *ha)
{
	if (ha->fce)
		dma_free_coherent(&ha->pdev->dev,
		    FCE_SIZE, ha->fce, ha->fce_dma);

	if (ha->eft)
		dma_free_coherent(&ha->pdev->dev,
		    EFT_SIZE, ha->eft, ha->eft_dma);

	if (ha->fw_dump)
		vfree(ha->fw_dump);
	if (ha->fw_dump_template)
		vfree(ha->fw_dump_template);

	ha->fce = NULL;
	ha->fce_dma = 0;
	ha->eft = NULL;
	ha->eft_dma = 0;
	ha->fw_dumped = 0;
	ha->fw_dump_cap_flags = 0;
	ha->fw_dump_reading = 0;
	ha->fw_dump = NULL;
	ha->fw_dump_len = 0;
	ha->fw_dump_template = NULL;
	ha->fw_dump_template_len = 0;
}