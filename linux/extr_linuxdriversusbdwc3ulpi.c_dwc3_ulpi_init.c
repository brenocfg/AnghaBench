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
struct dwc3 {int /*<<< orphan*/  ulpi; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc3_ulpi_ops ; 
 int /*<<< orphan*/  ulpi_register_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int dwc3_ulpi_init(struct dwc3 *dwc)
{
	/* Register the interface */
	dwc->ulpi = ulpi_register_interface(dwc->dev, &dwc3_ulpi_ops);
	if (IS_ERR(dwc->ulpi)) {
		dev_err(dwc->dev, "failed to register ULPI interface");
		return PTR_ERR(dwc->ulpi);
	}

	return 0;
}