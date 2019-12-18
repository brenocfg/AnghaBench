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

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  CONFIG_ACPI_NFIT ; 
 int /*<<< orphan*/  CONFIG_BLK_DEV_PMEM ; 
 int /*<<< orphan*/  CONFIG_DEV_DAX ; 
 int /*<<< orphan*/  CONFIG_DEV_DAX_PMEM ; 
 int /*<<< orphan*/  CONFIG_LIBNVDIMM ; 
 int /*<<< orphan*/  CONFIG_ND_BLK ; 
 int /*<<< orphan*/  CONFIG_ND_BTT ; 
 int /*<<< orphan*/  CONFIG_ND_PFN ; 
 int /*<<< orphan*/  IS_MODULE (int /*<<< orphan*/ ) ; 

void check(void)
{
	/*
	 * These kconfig symbols must be set to "m" for nfit_test to
	 * load and operate.
	 */
	BUILD_BUG_ON(!IS_MODULE(CONFIG_LIBNVDIMM));
	BUILD_BUG_ON(!IS_MODULE(CONFIG_BLK_DEV_PMEM));
	BUILD_BUG_ON(!IS_MODULE(CONFIG_ND_BTT));
	BUILD_BUG_ON(!IS_MODULE(CONFIG_ND_PFN));
	BUILD_BUG_ON(!IS_MODULE(CONFIG_ND_BLK));
	BUILD_BUG_ON(!IS_MODULE(CONFIG_ACPI_NFIT));
	BUILD_BUG_ON(!IS_MODULE(CONFIG_DEV_DAX));
	BUILD_BUG_ON(!IS_MODULE(CONFIG_DEV_DAX_PMEM));
}