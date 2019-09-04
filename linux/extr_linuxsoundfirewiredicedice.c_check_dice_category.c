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
struct fw_unit {int /*<<< orphan*/  directory; } ;
struct fw_device {int* config_rom; } ;
struct fw_csr_iterator {int dummy; } ;

/* Variables and functions */
#define  CSR_MODEL 129 
#define  CSR_SPECIFIER_ID 128 
 unsigned int DICE_CATEGORY_ID ; 
 int ENODEV ; 
 unsigned int LOUD_CATEGORY_ID ; 
 int OUI_LOUD ; 
 int OUI_WEISS ; 
 unsigned int WEISS_CATEGORY_ID ; 
 int /*<<< orphan*/  fw_csr_iterator_init (struct fw_csr_iterator*,int /*<<< orphan*/ ) ; 
 scalar_t__ fw_csr_iterator_next (struct fw_csr_iterator*,int*,int*) ; 
 struct fw_device* fw_parent_device (struct fw_unit*) ; 

__attribute__((used)) static int check_dice_category(struct fw_unit *unit)
{
	struct fw_device *device = fw_parent_device(unit);
	struct fw_csr_iterator it;
	int key, val, vendor = -1, model = -1;
	unsigned int category;

	/*
	 * Check that GUID and unit directory are constructed according to DICE
	 * rules, i.e., that the specifier ID is the GUID's OUI, and that the
	 * GUID chip ID consists of the 8-bit category ID, the 10-bit product
	 * ID, and a 22-bit serial number.
	 */
	fw_csr_iterator_init(&it, unit->directory);
	while (fw_csr_iterator_next(&it, &key, &val)) {
		switch (key) {
		case CSR_SPECIFIER_ID:
			vendor = val;
			break;
		case CSR_MODEL:
			model = val;
			break;
		}
	}

	if (vendor == OUI_WEISS)
		category = WEISS_CATEGORY_ID;
	else if (vendor == OUI_LOUD)
		category = LOUD_CATEGORY_ID;
	else
		category = DICE_CATEGORY_ID;
	if (device->config_rom[3] != ((vendor << 8) | category) ||
	    device->config_rom[4] >> 22 != model)
		return -ENODEV;

	return 0;
}