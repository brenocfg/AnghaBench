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
struct version_info {int version; int last_comp_version; int flags; int /*<<< orphan*/  hdr_size; } ;
struct fdt_reserve_entry {int dummy; } ;
struct fdt_header {void* size_dt_struct; void* size_dt_strings; void* boot_cpuid_phys; void* totalsize; void* off_dt_strings; void* off_dt_struct; void* off_mem_rsvmap; void* last_comp_version; void* version; void* magic; } ;

/* Variables and functions */
 int ALIGN (int /*<<< orphan*/ ,int) ; 
 int FDT_MAGIC ; 
 int FTF_BOOTCPUID ; 
 int FTF_STRTABSIZE ; 
 int FTF_STRUCTSIZE ; 
 void* cpu_to_fdt32 (int) ; 
 int /*<<< orphan*/  memset (struct fdt_header*,int,int) ; 

__attribute__((used)) static void make_fdt_header(struct fdt_header *fdt,
			    struct version_info *vi,
			    int reservesize, int dtsize, int strsize,
			    int boot_cpuid_phys)
{
	int reserve_off;

	reservesize += sizeof(struct fdt_reserve_entry);

	memset(fdt, 0xff, sizeof(*fdt));

	fdt->magic = cpu_to_fdt32(FDT_MAGIC);
	fdt->version = cpu_to_fdt32(vi->version);
	fdt->last_comp_version = cpu_to_fdt32(vi->last_comp_version);

	/* Reserve map should be doubleword aligned */
	reserve_off = ALIGN(vi->hdr_size, 8);

	fdt->off_mem_rsvmap = cpu_to_fdt32(reserve_off);
	fdt->off_dt_struct = cpu_to_fdt32(reserve_off + reservesize);
	fdt->off_dt_strings = cpu_to_fdt32(reserve_off + reservesize
					  + dtsize);
	fdt->totalsize = cpu_to_fdt32(reserve_off + reservesize + dtsize + strsize);

	if (vi->flags & FTF_BOOTCPUID)
		fdt->boot_cpuid_phys = cpu_to_fdt32(boot_cpuid_phys);
	if (vi->flags & FTF_STRTABSIZE)
		fdt->size_dt_strings = cpu_to_fdt32(strsize);
	if (vi->flags & FTF_STRUCTSIZE)
		fdt->size_dt_struct = cpu_to_fdt32(dtsize);
}