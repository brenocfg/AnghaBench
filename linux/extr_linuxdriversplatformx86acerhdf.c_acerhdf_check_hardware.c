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
struct bios_settings {scalar_t__* version; scalar_t__* product; scalar_t__* vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMI_BIOS_VERSION ; 
 int /*<<< orphan*/  DMI_PRODUCT_NAME ; 
 int /*<<< orphan*/  DMI_SYS_VENDOR ; 
 int /*<<< orphan*/  DRV_VER ; 
 int EINVAL ; 
 struct bios_settings const* bios_cfg ; 
 struct bios_settings* bios_tbl ; 
 char* dmi_get_system_info (int /*<<< orphan*/ ) ; 
 char* force_bios ; 
 char* force_product ; 
 scalar_t__ kernelmode ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,char const*,...) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 scalar_t__ str_starts_with (char const*,scalar_t__*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int acerhdf_check_hardware(void)
{
	char const *vendor, *version, *product;
	const struct bios_settings *bt = NULL;

	/* get BIOS data */
	vendor  = dmi_get_system_info(DMI_SYS_VENDOR);
	version = dmi_get_system_info(DMI_BIOS_VERSION);
	product = dmi_get_system_info(DMI_PRODUCT_NAME);

	if (!vendor || !version || !product) {
		pr_err("error getting hardware information\n");
		return -EINVAL;
	}

	pr_info("Acer Aspire One Fan driver, v.%s\n", DRV_VER);

	if (force_bios[0]) {
		version = force_bios;
		pr_info("forcing BIOS version: %s\n", version);
		kernelmode = 0;
	}

	if (force_product[0]) {
		product = force_product;
		pr_info("forcing BIOS product: %s\n", product);
		kernelmode = 0;
	}

	if (verbose)
		pr_info("BIOS info: %s %s, product: %s\n",
			vendor, version, product);

	/* search BIOS version and vendor in BIOS settings table */
	for (bt = bios_tbl; bt->vendor[0]; bt++) {
		/*
		 * check if actual hardware BIOS vendor, product and version
		 * IDs start with the strings of BIOS table entry
		 */
		if (str_starts_with(vendor, bt->vendor) &&
				str_starts_with(product, bt->product) &&
				str_starts_with(version, bt->version)) {
			bios_cfg = bt;
			break;
		}
	}

	if (!bios_cfg) {
		pr_err("unknown (unsupported) BIOS version %s/%s/%s, please report, aborting!\n",
		       vendor, product, version);
		return -EINVAL;
	}

	/*
	 * if started with kernel mode off, prevent the kernel from switching
	 * off the fan
	 */
	if (!kernelmode) {
		pr_notice("Fan control off, to enable do:\n");
		pr_notice("echo -n \"enabled\" > /sys/class/thermal/thermal_zone0/mode\n");
	}

	return 0;
}