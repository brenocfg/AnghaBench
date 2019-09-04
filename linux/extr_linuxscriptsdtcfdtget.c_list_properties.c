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
struct fdt_property {int /*<<< orphan*/  nameoff; } ;

/* Variables and functions */
 int FDT_ERR_NOTFOUND ; 
 int /*<<< orphan*/  fdt32_to_cpu (int /*<<< orphan*/ ) ; 
 int fdt_first_property_offset (void const*,int) ; 
 struct fdt_property* fdt_get_property_by_offset (void const*,int,int /*<<< orphan*/ *) ; 
 int fdt_next_property_offset (void const*,int) ; 
 char* fdt_string (void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (char const*) ; 

__attribute__((used)) static int list_properties(const void *blob, int node)
{
	const struct fdt_property *data;
	const char *name;
	int prop;

	prop = fdt_first_property_offset(blob, node);
	do {
		/* Stop silently when there are no more properties */
		if (prop < 0)
			return prop == -FDT_ERR_NOTFOUND ? 0 : prop;
		data = fdt_get_property_by_offset(blob, prop, NULL);
		name = fdt_string(blob, fdt32_to_cpu(data->nameoff));
		if (name)
			puts(name);
		prop = fdt_next_property_offset(blob, prop);
	} while (1);
}