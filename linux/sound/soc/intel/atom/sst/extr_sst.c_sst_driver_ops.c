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
struct intel_sst_drv {int dev_id; int /*<<< orphan*/  dev; int /*<<< orphan*/ * ops; int /*<<< orphan*/  tstamp; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SST_BYT_ACPI_ID 130 
#define  SST_CHV_ACPI_ID 129 
#define  SST_MRFLD_PCI_ID 128 
 int /*<<< orphan*/  SST_TIME_STAMP_MRFLD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mrfld_ops ; 

int sst_driver_ops(struct intel_sst_drv *sst)
{

	switch (sst->dev_id) {
	case SST_MRFLD_PCI_ID:
	case SST_BYT_ACPI_ID:
	case SST_CHV_ACPI_ID:
		sst->tstamp = SST_TIME_STAMP_MRFLD;
		sst->ops = &mrfld_ops;
		return 0;

	default:
		dev_err(sst->dev,
			"SST Driver capabilities missing for dev_id: %x",
			sst->dev_id);
		return -EINVAL;
	};
}