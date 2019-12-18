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

/* Variables and functions */
 int FDT_ERR_BADMAGIC ; 
 int FDT_ERR_BADVERSION ; 
 int FDT_ERR_TRUNCATED ; 
 int FDT_FIRST_SUPPORTED_VERSION ; 
 scalar_t__ FDT_LAST_SUPPORTED_VERSION ; 
 scalar_t__ FDT_MAGIC ; 
 size_t INT_MAX ; 
 int /*<<< orphan*/  check_block_ (size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_off_ (size_t,size_t,int /*<<< orphan*/ ) ; 
 size_t fdt_header_size (void const*) ; 
 int fdt_last_comp_version (void const*) ; 
 scalar_t__ fdt_magic (void const*) ; 
 int /*<<< orphan*/  fdt_off_dt_strings (void const*) ; 
 int /*<<< orphan*/  fdt_off_dt_struct (void const*) ; 
 int /*<<< orphan*/  fdt_off_mem_rsvmap (void const*) ; 
 int /*<<< orphan*/  fdt_size_dt_strings (void const*) ; 
 int /*<<< orphan*/  fdt_size_dt_struct (void const*) ; 
 size_t fdt_totalsize (void const*) ; 
 int fdt_version (void const*) ; 

int fdt_check_header(const void *fdt)
{
	size_t hdrsize;

	if (fdt_magic(fdt) != FDT_MAGIC)
		return -FDT_ERR_BADMAGIC;
	hdrsize = fdt_header_size(fdt);
	if ((fdt_version(fdt) < FDT_FIRST_SUPPORTED_VERSION)
	    || (fdt_last_comp_version(fdt) > FDT_LAST_SUPPORTED_VERSION))
		return -FDT_ERR_BADVERSION;
	if (fdt_version(fdt) < fdt_last_comp_version(fdt))
		return -FDT_ERR_BADVERSION;

	if ((fdt_totalsize(fdt) < hdrsize)
	    || (fdt_totalsize(fdt) > INT_MAX))
		return -FDT_ERR_TRUNCATED;

	/* Bounds check memrsv block */
	if (!check_off_(hdrsize, fdt_totalsize(fdt), fdt_off_mem_rsvmap(fdt)))
		return -FDT_ERR_TRUNCATED;

	/* Bounds check structure block */
	if (fdt_version(fdt) < 17) {
		if (!check_off_(hdrsize, fdt_totalsize(fdt),
				fdt_off_dt_struct(fdt)))
			return -FDT_ERR_TRUNCATED;
	} else {
		if (!check_block_(hdrsize, fdt_totalsize(fdt),
				  fdt_off_dt_struct(fdt),
				  fdt_size_dt_struct(fdt)))
			return -FDT_ERR_TRUNCATED;
	}

	/* Bounds check strings block */
	if (!check_block_(hdrsize, fdt_totalsize(fdt),
			  fdt_off_dt_strings(fdt), fdt_size_dt_strings(fdt)))
		return -FDT_ERR_TRUNCATED;

	return 0;
}