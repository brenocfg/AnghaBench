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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int FDT_ERR_NOPHANDLES ; 
 scalar_t__ FDT_MAX_PHANDLE ; 
 int fdt_find_max_phandle (void const*,scalar_t__*) ; 

int fdt_generate_phandle(const void *fdt, uint32_t *phandle)
{
	uint32_t max;
	int err;

	err = fdt_find_max_phandle(fdt, &max);
	if (err < 0)
		return err;

	if (max == FDT_MAX_PHANDLE)
		return -FDT_ERR_NOPHANDLES;

	if (phandle)
		*phandle = max + 1;

	return 0;
}