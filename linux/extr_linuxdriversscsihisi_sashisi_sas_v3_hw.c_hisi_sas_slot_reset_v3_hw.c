#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sas_ha_struct {struct hisi_hba* lldd_ha; } ;
struct pci_dev {int dummy; } ;
struct hisi_hba {int /*<<< orphan*/  wq; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
struct TYPE_3__ {scalar_t__ done; int /*<<< orphan*/  completion; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  HISI_SAS_DECLARE_RST_WORK_ON_STACK (TYPE_1__) ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct sas_ha_struct* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ r ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ ) ; 

__attribute__((used)) static pci_ers_result_t hisi_sas_slot_reset_v3_hw(struct pci_dev *pdev)
{
	struct sas_ha_struct *sha = pci_get_drvdata(pdev);
	struct hisi_hba *hisi_hba = sha->lldd_ha;
	struct device *dev = hisi_hba->dev;
	HISI_SAS_DECLARE_RST_WORK_ON_STACK(r);

	dev_info(dev, "PCI error: slot reset callback!!\n");
	queue_work(hisi_hba->wq, &r.work);
	wait_for_completion(r.completion);
	if (r.done)
		return PCI_ERS_RESULT_RECOVERED;

	return PCI_ERS_RESULT_DISCONNECT;
}