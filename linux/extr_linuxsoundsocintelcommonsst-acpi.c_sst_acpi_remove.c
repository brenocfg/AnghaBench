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
struct sst_pdata {int /*<<< orphan*/  fw; } ;
struct sst_acpi_priv {int /*<<< orphan*/  pdev_pcm; int /*<<< orphan*/  pdev_mach; struct sst_pdata sst_pdata; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 struct sst_acpi_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sst_acpi_remove(struct platform_device *pdev)
{
	struct sst_acpi_priv *sst_acpi = platform_get_drvdata(pdev);
	struct sst_pdata *sst_pdata = &sst_acpi->sst_pdata;

	platform_device_unregister(sst_acpi->pdev_mach);
	if (!IS_ERR_OR_NULL(sst_acpi->pdev_pcm))
		platform_device_unregister(sst_acpi->pdev_pcm);
	release_firmware(sst_pdata->fw);

	return 0;
}