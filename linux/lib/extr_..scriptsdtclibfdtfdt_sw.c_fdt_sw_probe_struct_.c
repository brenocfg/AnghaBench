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
 int FDT_ERR_BADSTATE ; 
 scalar_t__ fdt_off_dt_strings (void*) ; 
 int fdt_sw_probe_ (void*) ; 
 scalar_t__ fdt_totalsize (void*) ; 

__attribute__((used)) static int fdt_sw_probe_struct_(void *fdt)
{
	int err = fdt_sw_probe_(fdt);
	if (err)
		return err;

	if (fdt_off_dt_strings(fdt) != fdt_totalsize(fdt))
		return -FDT_ERR_BADSTATE;
	return 0;
}