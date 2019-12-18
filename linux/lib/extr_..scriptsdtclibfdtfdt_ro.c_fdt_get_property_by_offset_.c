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
struct fdt_property {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int fdt32_ld (int /*<<< orphan*/ *) ; 
 int fdt_check_prop_offset_ (void const*,int) ; 
 struct fdt_property* fdt_offset_ptr_ (void const*,int) ; 

__attribute__((used)) static const struct fdt_property *fdt_get_property_by_offset_(const void *fdt,
						              int offset,
						              int *lenp)
{
	int err;
	const struct fdt_property *prop;

	if ((err = fdt_check_prop_offset_(fdt, offset)) < 0) {
		if (lenp)
			*lenp = err;
		return NULL;
	}

	prop = fdt_offset_ptr_(fdt, offset);

	if (lenp)
		*lenp = fdt32_ld(&prop->len);

	return prop;
}