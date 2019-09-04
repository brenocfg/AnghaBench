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
struct pwm_lpss_chip {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct pwm_lpss_chip* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_forbid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwm_lpss_remove (struct pwm_lpss_chip*) ; 

__attribute__((used)) static void pwm_lpss_remove_pci(struct pci_dev *pdev)
{
	struct pwm_lpss_chip *lpwm = pci_get_drvdata(pdev);

	pm_runtime_forbid(&pdev->dev);
	pm_runtime_get_sync(&pdev->dev);

	pwm_lpss_remove(lpwm);
}