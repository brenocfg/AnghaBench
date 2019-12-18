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
 int fdt_add_reservemap_entry (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_set_off_dt_strings (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_totalsize (void*) ; 

int fdt_finish_reservemap(void *fdt)
{
	int err = fdt_add_reservemap_entry(fdt, 0, 0);

	if (err)
		return err;

	fdt_set_off_dt_strings(fdt, fdt_totalsize(fdt));
	return 0;
}