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
struct platform_device {int dummy; } ;
struct hisi_hba {int queue_count; int n_phy; struct platform_device* platform_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHL_INT1_MSK ; 
 int /*<<< orphan*/  CHL_INT2_MSK ; 
 scalar_t__ ENT_INT_SRC_MSK1 ; 
 scalar_t__ ENT_INT_SRC_MSK2 ; 
 scalar_t__ ENT_INT_SRC_MSK3 ; 
 scalar_t__ OQ0_INT_SRC_MSK ; 
 scalar_t__ SAS_ECC_INTR_MSK ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hisi_sas_write32 (struct hisi_hba*,scalar_t__,int) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void interrupt_disable_v2_hw(struct hisi_hba *hisi_hba)
{
	struct platform_device *pdev = hisi_hba->platform_dev;
	int i;

	for (i = 0; i < hisi_hba->queue_count; i++)
		hisi_sas_write32(hisi_hba, OQ0_INT_SRC_MSK + 0x4 * i, 0x1);

	hisi_sas_write32(hisi_hba, ENT_INT_SRC_MSK1, 0xffffffff);
	hisi_sas_write32(hisi_hba, ENT_INT_SRC_MSK2, 0xffffffff);
	hisi_sas_write32(hisi_hba, ENT_INT_SRC_MSK3, 0xffffffff);
	hisi_sas_write32(hisi_hba, SAS_ECC_INTR_MSK, 0xffffffff);

	for (i = 0; i < hisi_hba->n_phy; i++) {
		hisi_sas_phy_write32(hisi_hba, i, CHL_INT1_MSK, 0xffffffff);
		hisi_sas_phy_write32(hisi_hba, i, CHL_INT2_MSK, 0xffffffff);
	}

	for (i = 0; i < 128; i++)
		synchronize_irq(platform_get_irq(pdev, i));
}