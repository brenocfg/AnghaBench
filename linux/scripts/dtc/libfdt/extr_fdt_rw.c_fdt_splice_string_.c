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
 int fdt_off_dt_strings (void*) ; 
 int /*<<< orphan*/  fdt_set_size_dt_strings (void*,int) ; 
 int fdt_size_dt_strings (void*) ; 
 int fdt_splice_ (void*,void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fdt_splice_string_(void *fdt, int newlen)
{
	void *p = (char *)fdt
		+ fdt_off_dt_strings(fdt) + fdt_size_dt_strings(fdt);
	int err;

	if ((err = fdt_splice_(fdt, p, 0, newlen)))
		return err;

	fdt_set_size_dt_strings(fdt, fdt_size_dt_strings(fdt) + newlen);
	return 0;
}