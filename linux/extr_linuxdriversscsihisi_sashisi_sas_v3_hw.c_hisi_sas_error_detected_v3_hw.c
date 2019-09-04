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
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  int /*<<< orphan*/  pci_channel_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_CAN_RECOVER ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_channel_io_perm_failure ; 
 struct sas_ha_struct* pci_get_drvdata (struct pci_dev*) ; 
 scalar_t__ process_non_fatal_error_v3_hw (struct hisi_hba*) ; 

__attribute__((used)) static pci_ers_result_t hisi_sas_error_detected_v3_hw(struct pci_dev *pdev,
		pci_channel_state_t state)
{
	struct sas_ha_struct *sha = pci_get_drvdata(pdev);
	struct hisi_hba *hisi_hba = sha->lldd_ha;
	struct device *dev = hisi_hba->dev;

	dev_info(dev, "PCI error: detected callback, state(%d)!!\n", state);
	if (state == pci_channel_io_perm_failure)
		return PCI_ERS_RESULT_DISCONNECT;

	if (process_non_fatal_error_v3_hw(hisi_hba))
		return PCI_ERS_RESULT_NEED_RESET;

	return PCI_ERS_RESULT_CAN_RECOVER;
}