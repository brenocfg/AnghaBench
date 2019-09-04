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
typedef  int u32 ;
struct hisi_sas_hw_error {int irq_msk; int /*<<< orphan*/  msg; } ;
struct hisi_hba {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct hisi_sas_hw_error*) ; 
 int /*<<< orphan*/  SAS_RAS_INTR0 ; 
 int /*<<< orphan*/  SAS_RAS_INTR1 ; 
 int /*<<< orphan*/  SAS_RAS_INTR2 ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int hisi_sas_read32 (struct hisi_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_write32 (struct hisi_hba*,int /*<<< orphan*/ ,int) ; 
 struct hisi_sas_hw_error* sas_ras_intr0_nfe ; 
 struct hisi_sas_hw_error* sas_ras_intr1_nfe ; 
 struct hisi_sas_hw_error* sas_ras_intr2_nfe ; 

__attribute__((used)) static bool process_non_fatal_error_v3_hw(struct hisi_hba *hisi_hba)
{
	struct device *dev = hisi_hba->dev;
	const struct hisi_sas_hw_error *ras_error;
	bool need_reset = false;
	u32 irq_value;
	int i;

	irq_value = hisi_sas_read32(hisi_hba, SAS_RAS_INTR0);
	for (i = 0; i < ARRAY_SIZE(sas_ras_intr0_nfe); i++) {
		ras_error = &sas_ras_intr0_nfe[i];
		if (ras_error->irq_msk & irq_value) {
			dev_warn(dev, "SAS_RAS_INTR0: %s(irq_value=0x%x) found.\n",
					ras_error->msg, irq_value);
			need_reset = true;
		}
	}
	hisi_sas_write32(hisi_hba, SAS_RAS_INTR0, irq_value);

	irq_value = hisi_sas_read32(hisi_hba, SAS_RAS_INTR1);
	for (i = 0; i < ARRAY_SIZE(sas_ras_intr1_nfe); i++) {
		ras_error = &sas_ras_intr1_nfe[i];
		if (ras_error->irq_msk & irq_value) {
			dev_warn(dev, "SAS_RAS_INTR1: %s(irq_value=0x%x) found.\n",
					ras_error->msg, irq_value);
			need_reset = true;
		}
	}
	hisi_sas_write32(hisi_hba, SAS_RAS_INTR1, irq_value);

	irq_value = hisi_sas_read32(hisi_hba, SAS_RAS_INTR2);
	for (i = 0; i < ARRAY_SIZE(sas_ras_intr2_nfe); i++) {
		ras_error = &sas_ras_intr2_nfe[i];
		if (ras_error->irq_msk & irq_value) {
			dev_warn(dev, "SAS_RAS_INTR2: %s(irq_value=0x%x) found.\n",
					ras_error->msg, irq_value);
			need_reset = true;
		}
	}
	hisi_sas_write32(hisi_hba, SAS_RAS_INTR2, irq_value);

	return need_reset;
}