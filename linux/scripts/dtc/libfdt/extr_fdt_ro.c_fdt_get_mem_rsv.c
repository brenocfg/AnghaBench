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
struct fdt_reserve_entry {int /*<<< orphan*/  size; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int FDT_ERR_BADOFFSET ; 
 int /*<<< orphan*/  FDT_RO_PROBE (void const*) ; 
 int /*<<< orphan*/  fdt64_ld (int /*<<< orphan*/ *) ; 
 struct fdt_reserve_entry* fdt_mem_rsv (void const*,int) ; 

int fdt_get_mem_rsv(const void *fdt, int n, uint64_t *address, uint64_t *size)
{
	const struct fdt_reserve_entry *re;

	FDT_RO_PROBE(fdt);
	re = fdt_mem_rsv(fdt, n);
	if (!re)
		return -FDT_ERR_BADOFFSET;

	*address = fdt64_ld(&re->address);
	*size = fdt64_ld(&re->size);
	return 0;
}