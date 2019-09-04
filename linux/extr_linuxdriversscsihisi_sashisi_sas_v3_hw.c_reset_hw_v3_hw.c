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
typedef  int /*<<< orphan*/  u32 ;
struct hisi_hba {struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_HANDLE (struct device*) ; 
 int /*<<< orphan*/  AXI_CFG ; 
 int /*<<< orphan*/  DLVRY_QUEUE_ENABLE ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  acpi_evaluate_object (scalar_t__,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int hisi_sas_read32_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  hisi_sas_stop_phys (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_write32 (struct hisi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int reset_hw_v3_hw(struct hisi_hba *hisi_hba)
{
	struct device *dev = hisi_hba->dev;
	int ret;
	u32 val;

	hisi_sas_write32(hisi_hba, DLVRY_QUEUE_ENABLE, 0);

	/* Disable all of the PHYs */
	hisi_sas_stop_phys(hisi_hba);
	udelay(50);

	/* Ensure axi bus idle */
	ret = hisi_sas_read32_poll_timeout(AXI_CFG, val, !val,
					   20000, 1000000);
	if (ret) {
		dev_err(dev, "axi bus is not idle, ret = %d!\n", ret);
		return -EIO;
	}

	if (ACPI_HANDLE(dev)) {
		acpi_status s;

		s = acpi_evaluate_object(ACPI_HANDLE(dev), "_RST", NULL, NULL);
		if (ACPI_FAILURE(s)) {
			dev_err(dev, "Reset failed\n");
			return -EIO;
		}
	} else {
		dev_err(dev, "no reset method!\n");
		return -EINVAL;
	}

	return 0;
}