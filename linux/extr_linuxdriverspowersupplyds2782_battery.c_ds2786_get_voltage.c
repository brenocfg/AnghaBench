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
struct ds278x_info {int dummy; } ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  DS278x_REG_VOLT_MSB ; 
 int ds278x_read_reg16 (struct ds278x_info*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ds2786_get_voltage(struct ds278x_info *info, int *voltage_uV)
{
	s16 raw;
	int err;

	/*
	 * Voltage is measured in units of 1.22mV. The voltage is stored as
	 * a 12-bit number plus sign, in the upper bits of a 16-bit register
	 */
	err = ds278x_read_reg16(info, DS278x_REG_VOLT_MSB, &raw);
	if (err)
		return err;
	*voltage_uV = (raw / 8) * 1220;
	return 0;
}