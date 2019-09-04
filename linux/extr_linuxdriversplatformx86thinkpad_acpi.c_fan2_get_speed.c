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
typedef  int u8 ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
#define  TPACPI_FAN_RD_TPEC 128 
 int /*<<< orphan*/  acpi_ec_read (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  fan_rpm_offset ; 
 int /*<<< orphan*/  fan_select_fan1 () ; 
 int /*<<< orphan*/  fan_select_fan2 () ; 
 int fan_status_access_mode ; 
 int /*<<< orphan*/  likely (unsigned int*) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static int fan2_get_speed(unsigned int *speed)
{
	u8 hi, lo;
	bool rc;

	switch (fan_status_access_mode) {
	case TPACPI_FAN_RD_TPEC:
		/* all except 570, 600e/x, 770e, 770x */
		if (unlikely(!fan_select_fan2()))
			return -EIO;
		rc = !acpi_ec_read(fan_rpm_offset, &lo) ||
			     !acpi_ec_read(fan_rpm_offset + 1, &hi);
		fan_select_fan1(); /* play it safe */
		if (rc)
			return -EIO;

		if (likely(speed))
			*speed = (hi << 8) | lo;

		break;

	default:
		return -ENXIO;
	}

	return 0;
}