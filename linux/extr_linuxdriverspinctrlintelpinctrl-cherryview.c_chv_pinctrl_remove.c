#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct chv_pinctrl {TYPE_1__* community; } ;
struct TYPE_2__ {int /*<<< orphan*/  acpi_space_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_remove_address_space_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chv_pinctrl_mmio_access_handler ; 
 struct chv_pinctrl* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int chv_pinctrl_remove(struct platform_device *pdev)
{
	struct chv_pinctrl *pctrl = platform_get_drvdata(pdev);

	acpi_remove_address_space_handler(ACPI_COMPANION(&pdev->dev),
					  pctrl->community->acpi_space_id,
					  chv_pinctrl_mmio_access_handler);

	return 0;
}