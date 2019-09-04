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
struct ds278x_info {int rsns; } ;
typedef  int s16 ;

/* Variables and functions */
 int DS2786_CURRENT_UNITS ; 
 int /*<<< orphan*/  DS278x_REG_CURRENT_MSB ; 
 int ds278x_read_reg16 (struct ds278x_info*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ds2786_get_current(struct ds278x_info *info, int *current_uA)
{
	int err;
	s16 raw;

	err = ds278x_read_reg16(info, DS278x_REG_CURRENT_MSB, &raw);
	if (err)
		return err;
	*current_uA = (raw / 16) * (DS2786_CURRENT_UNITS / info->rsns);
	return 0;
}