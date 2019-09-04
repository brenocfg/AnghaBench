#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct proc_thermal_device {int /*<<< orphan*/ * soc_dts; } ;
struct pci_device_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct pci_dev {scalar_t__ device; TYPE_1__ dev; scalar_t__ irq; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  INTEL_SOC_DTS_INTERRUPT_MSI ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ PCI_DEVICE_ID_PROC_BSW_THERMAL ; 
 scalar_t__ PROC_THERMAL_PCI ; 
 scalar_t__ PROC_THERMAL_PLATFORM_DEV ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  intel_soc_dts_iosf_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intel_soc_dts_iosf_init (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int pci_enable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct proc_thermal_device*) ; 
 int /*<<< orphan*/  power_limit_attribute_group ; 
 int proc_thermal_add (TYPE_1__*,struct proc_thermal_device**) ; 
 scalar_t__ proc_thermal_emum_mode ; 
 int /*<<< orphan*/  proc_thermal_pci_msi_irq ; 
 int request_threaded_irq (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pci_dev*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int  proc_thermal_pci_probe(struct pci_dev *pdev,
				   const struct pci_device_id *unused)
{
	struct proc_thermal_device *proc_priv;
	int ret;

	if (proc_thermal_emum_mode == PROC_THERMAL_PLATFORM_DEV) {
		dev_err(&pdev->dev, "error: enumerated as platform dev\n");
		return -ENODEV;
	}

	ret = pci_enable_device(pdev);
	if (ret < 0) {
		dev_err(&pdev->dev, "error: could not enable device\n");
		return ret;
	}

	ret = proc_thermal_add(&pdev->dev, &proc_priv);
	if (ret) {
		pci_disable_device(pdev);
		return ret;
	}

	pci_set_drvdata(pdev, proc_priv);
	proc_thermal_emum_mode = PROC_THERMAL_PCI;

	if (pdev->device == PCI_DEVICE_ID_PROC_BSW_THERMAL) {
		/*
		 * Enumerate additional DTS sensors available via IOSF.
		 * But we are not treating as a failure condition, if
		 * there are no aux DTSs enabled or fails. This driver
		 * already exposes sensors, which can be accessed via
		 * ACPI/MSR. So we don't want to fail for auxiliary DTSs.
		 */
		proc_priv->soc_dts = intel_soc_dts_iosf_init(
					INTEL_SOC_DTS_INTERRUPT_MSI, 2, 0);

		if (!IS_ERR(proc_priv->soc_dts) && pdev->irq) {
			ret = pci_enable_msi(pdev);
			if (!ret) {
				ret = request_threaded_irq(pdev->irq, NULL,
						proc_thermal_pci_msi_irq,
						IRQF_ONESHOT, "proc_thermal",
						pdev);
				if (ret) {
					intel_soc_dts_iosf_exit(
							proc_priv->soc_dts);
					pci_disable_msi(pdev);
					proc_priv->soc_dts = NULL;
				}
			}
		} else
			dev_err(&pdev->dev, "No auxiliary DTSs enabled\n");
	}

	dev_info(&pdev->dev, "Creating sysfs group for PROC_THERMAL_PCI\n");

	return sysfs_create_group(&pdev->dev.kobj,
					 &power_limit_attribute_group);
}