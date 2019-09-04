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
 int /*<<< orphan*/  TPACPI_MAIL ; 
 int TP_ACPI_MULTI_MODE_FLAT ; 
 int TP_ACPI_MULTI_MODE_INVALID ; 
 int TP_ACPI_MULTI_MODE_LAPTOP ; 
 int TP_ACPI_MULTI_MODE_STAND ; 
 int TP_ACPI_MULTI_MODE_STAND_TENT ; 
 int TP_ACPI_MULTI_MODE_TABLET ; 
 int TP_ACPI_MULTI_MODE_TABLET_LIKE ; 
 int TP_ACPI_MULTI_MODE_TENT ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int hotkey_gmms_get_tablet_mode(int s, int *has_tablet_mode)
{
	int type = (s >> 16) & 0xffff;
	int value = s & 0xffff;
	int mode = TP_ACPI_MULTI_MODE_INVALID;
	int valid_modes = 0;

	if (has_tablet_mode)
		*has_tablet_mode = 0;

	switch (type) {
	case 1:
		valid_modes = TP_ACPI_MULTI_MODE_LAPTOP |
			      TP_ACPI_MULTI_MODE_TABLET |
			      TP_ACPI_MULTI_MODE_STAND_TENT;
		break;
	case 2:
		valid_modes = TP_ACPI_MULTI_MODE_LAPTOP |
			      TP_ACPI_MULTI_MODE_FLAT |
			      TP_ACPI_MULTI_MODE_TABLET |
			      TP_ACPI_MULTI_MODE_STAND |
			      TP_ACPI_MULTI_MODE_TENT;
		break;
	case 3:
		valid_modes = TP_ACPI_MULTI_MODE_LAPTOP |
			      TP_ACPI_MULTI_MODE_FLAT;
		break;
	case 4:
	case 5:
		/* In mode 4, FLAT is not specified as a valid mode. However,
		 * it can be seen at least on the X1 Yoga 2nd Generation.
		 */
		valid_modes = TP_ACPI_MULTI_MODE_LAPTOP |
			      TP_ACPI_MULTI_MODE_FLAT |
			      TP_ACPI_MULTI_MODE_TABLET |
			      TP_ACPI_MULTI_MODE_STAND |
			      TP_ACPI_MULTI_MODE_TENT;
		break;
	default:
		pr_err("Unknown multi mode status type %d with value 0x%04X, please report this to %s\n",
		       type, value, TPACPI_MAIL);
		return 0;
	}

	if (has_tablet_mode && (valid_modes & TP_ACPI_MULTI_MODE_TABLET_LIKE))
		*has_tablet_mode = 1;

	switch (value) {
	case 1:
		mode = TP_ACPI_MULTI_MODE_LAPTOP;
		break;
	case 2:
		mode = TP_ACPI_MULTI_MODE_FLAT;
		break;
	case 3:
		mode = TP_ACPI_MULTI_MODE_TABLET;
		break;
	case 4:
		if (type == 1)
			mode = TP_ACPI_MULTI_MODE_STAND_TENT;
		else
			mode = TP_ACPI_MULTI_MODE_STAND;
		break;
	case 5:
		mode = TP_ACPI_MULTI_MODE_TENT;
		break;
	default:
		if (type == 5 && value == 0xffff) {
			pr_warn("Multi mode status is undetected, assuming laptop\n");
			return 0;
		}
	}

	if (!(mode & valid_modes)) {
		pr_err("Unknown/reserved multi mode value 0x%04X for type %d, please report this to %s\n",
		       value, type, TPACPI_MAIL);
		return 0;
	}

	return !!(mode & TP_ACPI_MULTI_MODE_TABLET_LIKE);
}