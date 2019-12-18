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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  fdt64_t ;
typedef  int /*<<< orphan*/  fdt32_t ;

/* Variables and functions */
 int FDT_ERR_BADNCELLS ; 
 int FDT_ERR_BADVALUE ; 
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  fdt32_st (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt64_st (int /*<<< orphan*/ *,scalar_t__) ; 
 int fdt_address_cells (void*,int) ; 
 int fdt_appendprop (void*,int,char const*,int /*<<< orphan*/ *,int) ; 
 int fdt_size_cells (void*,int) ; 

int fdt_appendprop_addrrange(void *fdt, int parent, int nodeoffset,
			     const char *name, uint64_t addr, uint64_t size)
{
	int addr_cells, size_cells, ret;
	uint8_t data[sizeof(fdt64_t) * 2], *prop;

	ret = fdt_address_cells(fdt, parent);
	if (ret < 0)
		return ret;
	addr_cells = ret;

	ret = fdt_size_cells(fdt, parent);
	if (ret < 0)
		return ret;
	size_cells = ret;

	/* check validity of address */
	prop = data;
	if (addr_cells == 1) {
		if ((addr > UINT32_MAX) || ((UINT32_MAX + 1 - addr) < size))
			return -FDT_ERR_BADVALUE;

		fdt32_st(prop, (uint32_t)addr);
	} else if (addr_cells == 2) {
		fdt64_st(prop, addr);
	} else {
		return -FDT_ERR_BADNCELLS;
	}

	/* check validity of size */
	prop += addr_cells * sizeof(fdt32_t);
	if (size_cells == 1) {
		if (size > UINT32_MAX)
			return -FDT_ERR_BADVALUE;

		fdt32_st(prop, (uint32_t)size);
	} else if (size_cells == 2) {
		fdt64_st(prop, size);
	} else {
		return -FDT_ERR_BADNCELLS;
	}

	return fdt_appendprop(fdt, nodeoffset, name, data,
			      (addr_cells + size_cells) * sizeof(fdt32_t));
}