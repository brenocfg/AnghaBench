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
typedef  int /*<<< orphan*/  uint64_t ;
struct fdt_reserve_entry {void* size; void* address; } ;

/* Variables and functions */
 int FDT_ERR_NOSPACE ; 
 int /*<<< orphan*/  FDT_SW_PROBE_MEMRSV (void*) ; 
 void* cpu_to_fdt64 (int /*<<< orphan*/ ) ; 
 int fdt_off_dt_struct (void*) ; 
 int /*<<< orphan*/  fdt_set_off_dt_struct (void*,int) ; 
 int fdt_totalsize (void*) ; 

int fdt_add_reservemap_entry(void *fdt, uint64_t addr, uint64_t size)
{
	struct fdt_reserve_entry *re;
	int offset;

	FDT_SW_PROBE_MEMRSV(fdt);

	offset = fdt_off_dt_struct(fdt);
	if ((offset + sizeof(*re)) > fdt_totalsize(fdt))
		return -FDT_ERR_NOSPACE;

	re = (struct fdt_reserve_entry *)((char *)fdt + offset);
	re->address = cpu_to_fdt64(addr);
	re->size = cpu_to_fdt64(size);

	fdt_set_off_dt_struct(fdt, offset + sizeof(*re));

	return 0;
}