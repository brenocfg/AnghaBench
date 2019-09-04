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
struct hisi_hba {struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HGC_DQ_ECC_ADDR ; 
 int HGC_DQ_ECC_ADDR_BAD_MSK ; 
 int HGC_DQ_ECC_ADDR_BAD_OFF ; 
 int /*<<< orphan*/  HGC_ECC_ERR ; 
 int /*<<< orphan*/  HGC_IOST_ECC_ADDR ; 
 int HGC_IOST_ECC_ADDR_BAD_MSK ; 
 int HGC_IOST_ECC_ADDR_BAD_OFF ; 
 int /*<<< orphan*/  HGC_ITCT_ECC_ADDR ; 
 int HGC_ITCT_ECC_ADDR_BAD_MSK ; 
 int HGC_ITCT_ECC_ADDR_BAD_OFF ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SAS_ECC_INTR ; 
 int SAS_ECC_INTR_DQ_ECC1B_MSK ; 
 int SAS_ECC_INTR_DQ_ECCBAD_MSK ; 
 int SAS_ECC_INTR_IOST_ECC1B_MSK ; 
 int SAS_ECC_INTR_IOST_ECCBAD_MSK ; 
 int SAS_ECC_INTR_ITCT_ECC1B_MSK ; 
 int SAS_ECC_INTR_ITCT_ECCBAD_MSK ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int hisi_sas_read32 (struct hisi_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_write32 (struct hisi_hba*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t fatal_ecc_int_v1_hw(int irq, void *p)
{
	struct hisi_hba *hisi_hba = p;
	struct device *dev = hisi_hba->dev;
	u32 ecc_int = hisi_sas_read32(hisi_hba, SAS_ECC_INTR);

	if (ecc_int & SAS_ECC_INTR_DQ_ECC1B_MSK) {
		u32 ecc_err = hisi_sas_read32(hisi_hba, HGC_ECC_ERR);

		panic("%s: Fatal DQ 1b ECC interrupt (0x%x)\n",
		      dev_name(dev), ecc_err);
	}

	if (ecc_int & SAS_ECC_INTR_DQ_ECCBAD_MSK) {
		u32 addr = (hisi_sas_read32(hisi_hba, HGC_DQ_ECC_ADDR) &
				HGC_DQ_ECC_ADDR_BAD_MSK) >>
				HGC_DQ_ECC_ADDR_BAD_OFF;

		panic("%s: Fatal DQ RAM ECC interrupt @ 0x%08x\n",
		      dev_name(dev), addr);
	}

	if (ecc_int & SAS_ECC_INTR_IOST_ECC1B_MSK) {
		u32 ecc_err = hisi_sas_read32(hisi_hba, HGC_ECC_ERR);

		panic("%s: Fatal IOST 1b ECC interrupt (0x%x)\n",
		      dev_name(dev), ecc_err);
	}

	if (ecc_int & SAS_ECC_INTR_IOST_ECCBAD_MSK) {
		u32 addr = (hisi_sas_read32(hisi_hba, HGC_IOST_ECC_ADDR) &
				HGC_IOST_ECC_ADDR_BAD_MSK) >>
				HGC_IOST_ECC_ADDR_BAD_OFF;

		panic("%s: Fatal IOST RAM ECC interrupt @ 0x%08x\n",
		      dev_name(dev), addr);
	}

	if (ecc_int & SAS_ECC_INTR_ITCT_ECCBAD_MSK) {
		u32 addr = (hisi_sas_read32(hisi_hba, HGC_ITCT_ECC_ADDR) &
				HGC_ITCT_ECC_ADDR_BAD_MSK) >>
				HGC_ITCT_ECC_ADDR_BAD_OFF;

		panic("%s: Fatal TCT RAM ECC interrupt @ 0x%08x\n",
		      dev_name(dev), addr);
	}

	if (ecc_int & SAS_ECC_INTR_ITCT_ECC1B_MSK) {
		u32 ecc_err = hisi_sas_read32(hisi_hba, HGC_ECC_ERR);

		panic("%s: Fatal ITCT 1b ECC interrupt (0x%x)\n",
		      dev_name(dev), ecc_err);
	}

	hisi_sas_write32(hisi_hba, SAS_ECC_INTR, ecc_int | 0x3f);

	return IRQ_HANDLED;
}