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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct owl_ctx {int /*<<< orphan*/  eeprom_load; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct owl_ctx*) ; 
 struct owl_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  owl_fw_cb ; 
 char* owl_get_eeprom_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct owl_ctx*) ; 
 scalar_t__ pcim_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pcim_pin_device (struct pci_dev*) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int owl_probe(struct pci_dev *pdev,
		    const struct pci_device_id *id)
{
	struct owl_ctx *ctx;
	const char *eeprom_name;
	int err = 0;

	if (pcim_enable_device(pdev))
		return -EIO;

	pcim_pin_device(pdev);

	eeprom_name = owl_get_eeprom_name(pdev);
	if (!eeprom_name) {
		dev_err(&pdev->dev, "no eeprom filename found.\n");
		return -ENODEV;
	}

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx) {
		dev_err(&pdev->dev, "failed to alloc device context.\n");
		return -ENOMEM;
	}
	init_completion(&ctx->eeprom_load);

	pci_set_drvdata(pdev, ctx);
	err = request_firmware_nowait(THIS_MODULE, true, eeprom_name,
				      &pdev->dev, GFP_KERNEL, pdev, owl_fw_cb);
	if (err) {
		dev_err(&pdev->dev, "failed to request caldata (%d).\n", err);
		kfree(ctx);
	}
	return err;
}