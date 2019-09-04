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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int OF_ROOT_NODE_ADDR_CELLS_DEFAULT ; 
 int OF_ROOT_NODE_SIZE_CELLS_DEFAULT ; 
 int fdt32_to_cpu (int /*<<< orphan*/  const) ; 
 void* fdt_getprop (int /*<<< orphan*/ ,int,char*,int*) ; 
 int fdt_path_offset (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fdt_setprop (int /*<<< orphan*/ ,int,char*,void const*,int) ; 
 int /*<<< orphan*/  initial_boot_params ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

void of_fdt_limit_memory(int limit)
{
	int memory;
	int len;
	const void *val;
	int nr_address_cells = OF_ROOT_NODE_ADDR_CELLS_DEFAULT;
	int nr_size_cells = OF_ROOT_NODE_SIZE_CELLS_DEFAULT;
	const __be32 *addr_prop;
	const __be32 *size_prop;
	int root_offset;
	int cell_size;

	root_offset = fdt_path_offset(initial_boot_params, "/");
	if (root_offset < 0)
		return;

	addr_prop = fdt_getprop(initial_boot_params, root_offset,
				"#address-cells", NULL);
	if (addr_prop)
		nr_address_cells = fdt32_to_cpu(*addr_prop);

	size_prop = fdt_getprop(initial_boot_params, root_offset,
				"#size-cells", NULL);
	if (size_prop)
		nr_size_cells = fdt32_to_cpu(*size_prop);

	cell_size = sizeof(uint32_t)*(nr_address_cells + nr_size_cells);

	memory = fdt_path_offset(initial_boot_params, "/memory");
	if (memory > 0) {
		val = fdt_getprop(initial_boot_params, memory, "reg", &len);
		if (len > limit*cell_size) {
			len = limit*cell_size;
			pr_debug("Limiting number of entries to %d\n", limit);
			fdt_setprop(initial_boot_params, memory, "reg", val,
					len);
		}
	}
}