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
struct ipr_ioa_cfg {TYPE_1__* pdev; int /*<<< orphan*/  saved_pcix_cmd_reg; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCI_CAP_ID_PCIX ; 
 scalar_t__ PCI_X_CMD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int pci_find_capability (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_write_config_word (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipr_set_pcix_cmd_reg(struct ipr_ioa_cfg *ioa_cfg)
{
	int pcix_cmd_reg = pci_find_capability(ioa_cfg->pdev, PCI_CAP_ID_PCIX);

	if (pcix_cmd_reg) {
		if (pci_write_config_word(ioa_cfg->pdev, pcix_cmd_reg + PCI_X_CMD,
					  ioa_cfg->saved_pcix_cmd_reg) != PCIBIOS_SUCCESSFUL) {
			dev_err(&ioa_cfg->pdev->dev, "Failed to setup PCI-X command register\n");
			return -EIO;
		}
	}

	return 0;
}