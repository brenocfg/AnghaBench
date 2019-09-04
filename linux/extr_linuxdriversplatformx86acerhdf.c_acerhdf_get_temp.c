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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  tempreg; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* bios_cfg ; 
 scalar_t__ ec_read (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int acerhdf_get_temp(int *temp)
{
	u8 read_temp;

	if (ec_read(bios_cfg->tempreg, &read_temp))
		return -EINVAL;

	*temp = read_temp * 1000;

	return 0;
}