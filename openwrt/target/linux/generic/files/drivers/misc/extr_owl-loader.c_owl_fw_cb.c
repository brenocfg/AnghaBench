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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {struct pci_bus* bus; int /*<<< orphan*/  dev; } ;
struct pci_bus {int dummy; } ;
struct owl_ctx {int /*<<< orphan*/  eeprom_load; } ;
struct firmware {int size; scalar_t__ data; } ;
struct ath9k_platform_data {int /*<<< orphan*/ * eeprom_name; int /*<<< orphan*/  eeprom_data; } ;

/* Variables and functions */
 scalar_t__ ath9k_pci_fixup (struct pci_dev*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct ath9k_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_lock_rescan_remove () ; 
 int /*<<< orphan*/  pci_rescan_bus (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_stop_and_remove_bus_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_unlock_rescan_remove () ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 

__attribute__((used)) static void owl_fw_cb(const struct firmware *fw, void *context)
{
	struct pci_dev *pdev = (struct pci_dev *) context;
	struct owl_ctx *ctx = (struct owl_ctx *) pci_get_drvdata(pdev);
	struct ath9k_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct pci_bus *bus;

	complete(&ctx->eeprom_load);

	if (!fw) {
		dev_err(&pdev->dev, "no eeprom data received.\n");
		goto release;
	}

	/* also note that we are doing *u16 operations on the file */
	if (fw->size > sizeof(pdata->eeprom_data) || fw->size < 0x200 ||
	    (fw->size & 1) == 1) {
		dev_err(&pdev->dev, "eeprom file has an invalid size.\n");
		goto release;
	}

	if (pdata) {
		memcpy(pdata->eeprom_data, fw->data, fw->size);

		/*
		 * eeprom has been successfully loaded - pass the data to ath9k
		 * but remove the eeprom_name, so it doesn't try to load it too.
		 */
		pdata->eeprom_name = NULL;
	}

	if (ath9k_pci_fixup(pdev, (const u16 *) fw->data, fw->size))
		goto release;

	pci_lock_rescan_remove();
	bus = pdev->bus;
	pci_stop_and_remove_bus_device(pdev);
	/*
	 * the device should come back with the proper
	 * ProductId. But we have to initiate a rescan.
	 */
	pci_rescan_bus(bus);
	pci_unlock_rescan_remove();

release:
	release_firmware(fw);
}