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
typedef  int uint32_t ;
struct fdt_reserve_entry {int dummy; } ;
struct fdt_header {int dummy; } ;

/* Variables and functions */
 size_t FDT_ALIGN (int,int) ; 
 int FDT_CREATE_FLAGS_ALL ; 
 int FDT_ERR_BADFLAGS ; 
 int FDT_ERR_NOSPACE ; 
 int /*<<< orphan*/  FDT_LAST_SUPPORTED_VERSION ; 
 int /*<<< orphan*/  FDT_SW_MAGIC ; 
 int /*<<< orphan*/  fdt_off_mem_rsvmap (void*) ; 
 int /*<<< orphan*/  fdt_set_last_comp_version (void*,int) ; 
 int /*<<< orphan*/  fdt_set_magic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_set_off_dt_strings (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_set_off_dt_struct (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_set_off_mem_rsvmap (void*,size_t const) ; 
 int /*<<< orphan*/  fdt_set_totalsize (void*,int) ; 
 int /*<<< orphan*/  fdt_set_version (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

int fdt_create_with_flags(void *buf, int bufsize, uint32_t flags)
{
	const size_t hdrsize = FDT_ALIGN(sizeof(struct fdt_header),
					 sizeof(struct fdt_reserve_entry));
	void *fdt = buf;

	if (bufsize < hdrsize)
		return -FDT_ERR_NOSPACE;

	if (flags & ~FDT_CREATE_FLAGS_ALL)
		return -FDT_ERR_BADFLAGS;

	memset(buf, 0, bufsize);

	/*
	 * magic and last_comp_version keep intermediate state during the fdt
	 * creation process, which is replaced with the proper FDT format by
	 * fdt_finish().
	 *
	 * flags should be accessed with sw_flags().
	 */
	fdt_set_magic(fdt, FDT_SW_MAGIC);
	fdt_set_version(fdt, FDT_LAST_SUPPORTED_VERSION);
	fdt_set_last_comp_version(fdt, flags);

	fdt_set_totalsize(fdt,  bufsize);

	fdt_set_off_mem_rsvmap(fdt, hdrsize);
	fdt_set_off_dt_struct(fdt, fdt_off_mem_rsvmap(fdt));
	fdt_set_off_dt_strings(fdt, 0);

	return 0;
}