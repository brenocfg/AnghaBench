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
struct il_priv {int /*<<< orphan*/  ucode_boot; int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  ucode_init_data; int /*<<< orphan*/  ucode_init; int /*<<< orphan*/  ucode_data_backup; int /*<<< orphan*/  ucode_data; int /*<<< orphan*/  ucode_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  il_free_fw_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
il3945_dealloc_ucode_pci(struct il_priv *il)
{
	il_free_fw_desc(il->pci_dev, &il->ucode_code);
	il_free_fw_desc(il->pci_dev, &il->ucode_data);
	il_free_fw_desc(il->pci_dev, &il->ucode_data_backup);
	il_free_fw_desc(il->pci_dev, &il->ucode_init);
	il_free_fw_desc(il->pci_dev, &il->ucode_init_data);
	il_free_fw_desc(il->pci_dev, &il->ucode_boot);
}