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
struct pci_dev {scalar_t__ vendor; scalar_t__ device; int /*<<< orphan*/  dev; } ;
struct gpio_desc {int dummy; } ;
struct dwc3_pci {int has_dsm_for_pm; int /*<<< orphan*/  guid; struct pci_dev* pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_BXT ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_BXT_M ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_BYT ; 
 int /*<<< orphan*/  PCI_INTEL_BXT_DSM_GUID ; 
 scalar_t__ PCI_VENDOR_ID_INTEL ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  acpi_dwc3_byt_gpios ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int devm_acpi_dev_add_driver_gpios (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dwc3_byt_enable_ulpi_refclock (struct pci_dev*) ; 
 int /*<<< orphan*/  gpiod_add_lookup_table (int /*<<< orphan*/ *) ; 
 struct gpio_desc* gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_put (struct gpio_desc*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (struct gpio_desc*,int) ; 
 int /*<<< orphan*/  guid_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_bytcr_gpios ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int dwc3_pci_quirks(struct dwc3_pci *dwc)
{
	struct pci_dev			*pdev = dwc->pci;

	if (pdev->vendor == PCI_VENDOR_ID_INTEL) {
		if (pdev->device == PCI_DEVICE_ID_INTEL_BXT ||
				pdev->device == PCI_DEVICE_ID_INTEL_BXT_M) {
			guid_parse(PCI_INTEL_BXT_DSM_GUID, &dwc->guid);
			dwc->has_dsm_for_pm = true;
		}

		if (pdev->device == PCI_DEVICE_ID_INTEL_BYT) {
			struct gpio_desc *gpio;
			int ret;

			/* On BYT the FW does not always enable the refclock */
			ret = dwc3_byt_enable_ulpi_refclock(pdev);
			if (ret)
				return ret;

			ret = devm_acpi_dev_add_driver_gpios(&pdev->dev,
					acpi_dwc3_byt_gpios);
			if (ret)
				dev_dbg(&pdev->dev, "failed to add mapping table\n");

			/*
			 * A lot of BYT devices lack ACPI resource entries for
			 * the GPIOs, add a fallback mapping to the reference
			 * design GPIOs which all boards seem to use.
			 */
			gpiod_add_lookup_table(&platform_bytcr_gpios);

			/*
			 * These GPIOs will turn on the USB2 PHY. Note that we have to
			 * put the gpio descriptors again here because the phy driver
			 * might want to grab them, too.
			 */
			gpio = gpiod_get_optional(&pdev->dev, "cs", GPIOD_OUT_LOW);
			if (IS_ERR(gpio))
				return PTR_ERR(gpio);

			gpiod_set_value_cansleep(gpio, 1);
			gpiod_put(gpio);

			gpio = gpiod_get_optional(&pdev->dev, "reset", GPIOD_OUT_LOW);
			if (IS_ERR(gpio))
				return PTR_ERR(gpio);

			if (gpio) {
				gpiod_set_value_cansleep(gpio, 1);
				gpiod_put(gpio);
				usleep_range(10000, 11000);
			}
		}
	}

	return 0;
}