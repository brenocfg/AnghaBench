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
struct fdt_reserve_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ fdt_off_dt_strings (void*) ; 
 scalar_t__ fdt_off_dt_struct (void*) ; 
 int /*<<< orphan*/  fdt_set_off_dt_strings (void*,scalar_t__) ; 
 int /*<<< orphan*/  fdt_set_off_dt_struct (void*,scalar_t__) ; 
 int fdt_splice_ (void*,struct fdt_reserve_entry*,int,int) ; 

__attribute__((used)) static int fdt_splice_mem_rsv_(void *fdt, struct fdt_reserve_entry *p,
			       int oldn, int newn)
{
	int delta = (newn - oldn) * sizeof(*p);
	int err;
	err = fdt_splice_(fdt, p, oldn * sizeof(*p), newn * sizeof(*p));
	if (err)
		return err;
	fdt_set_off_dt_struct(fdt, fdt_off_dt_struct(fdt) + delta);
	fdt_set_off_dt_strings(fdt, fdt_off_dt_strings(fdt) + delta);
	return 0;
}