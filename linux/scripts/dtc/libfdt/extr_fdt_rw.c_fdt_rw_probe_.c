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
 int FDT_ERR_BADLAYOUT ; 
 int FDT_ERR_BADVERSION ; 
 int /*<<< orphan*/  FDT_RO_PROBE (void*) ; 
 scalar_t__ fdt_blocks_misordered_ (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_set_version (void*,int) ; 
 int /*<<< orphan*/  fdt_size_dt_struct (void*) ; 
 int fdt_version (void*) ; 

__attribute__((used)) static int fdt_rw_probe_(void *fdt)
{
	FDT_RO_PROBE(fdt);

	if (fdt_version(fdt) < 17)
		return -FDT_ERR_BADVERSION;
	if (fdt_blocks_misordered_(fdt, sizeof(struct fdt_reserve_entry),
				   fdt_size_dt_struct(fdt)))
		return -FDT_ERR_BADLAYOUT;
	if (fdt_version(fdt) > 17)
		fdt_set_version(fdt, 17);

	return 0;
}