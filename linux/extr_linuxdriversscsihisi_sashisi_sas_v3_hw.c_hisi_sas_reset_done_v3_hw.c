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
struct sas_ha_struct {struct hisi_hba* lldd_ha; } ;
struct pci_dev {int dummy; } ;
struct hisi_hba {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  hisi_sas_controller_reset_done (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_init_mem (struct hisi_hba*) ; 
 int hw_init_v3_hw (struct hisi_hba*) ; 
 struct sas_ha_struct* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void hisi_sas_reset_done_v3_hw(struct pci_dev *pdev)
{
	struct sas_ha_struct *sha = pci_get_drvdata(pdev);
	struct hisi_hba *hisi_hba = sha->lldd_ha;
	struct device *dev = hisi_hba->dev;
	int rc;

	hisi_sas_init_mem(hisi_hba);

	rc = hw_init_v3_hw(hisi_hba);
	if (rc) {
		dev_err(dev, "FLR: hw init failed rc=%d\n", rc);
		return;
	}

	hisi_sas_controller_reset_done(hisi_hba);
	dev_info(dev, "FLR done\n");
}