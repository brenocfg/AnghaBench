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
struct ili9320_reg {int /*<<< orphan*/  value; int /*<<< orphan*/  address; } ;
struct ili9320 {int dummy; } ;

/* Variables and functions */
 int ili9320_write (struct ili9320*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ili9320_write_regs(struct ili9320 *ili,
		       const struct ili9320_reg *values,
		       int nr_values)
{
	int index;
	int ret;

	for (index = 0; index < nr_values; index++, values++) {
		ret = ili9320_write(ili, values->address, values->value);
		if (ret != 0)
			return ret;
	}

	return 0;
}