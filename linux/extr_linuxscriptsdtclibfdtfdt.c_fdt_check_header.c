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
 int FDT_ERR_BADSTATE ; 
 int FDT_ERR_BADVERSION ; 
 scalar_t__ FDT_FIRST_SUPPORTED_VERSION ; 
 scalar_t__ FDT_LAST_SUPPORTED_VERSION ; 
 scalar_t__ FDT_MAGIC ; 
 scalar_t__ FDT_SW_MAGIC ; 
 scalar_t__ fdt_last_comp_version (void const*) ; 
 scalar_t__ fdt_magic (void const*) ; 
 scalar_t__ fdt_size_dt_struct (void const*) ; 
 scalar_t__ fdt_version (void const*) ; 

int fdt_check_header(const void *fdt)
{
	if (fdt_magic(fdt) == FDT_MAGIC) {
		/* Complete tree */
		if (fdt_version(fdt) < FDT_FIRST_SUPPORTED_VERSION)
			return -FDT_ERR_BADVERSION;
		if (fdt_last_comp_version(fdt) > FDT_LAST_SUPPORTED_VERSION)
			return -FDT_ERR_BADVERSION;
	} else if (fdt_magic(fdt) == FDT_SW_MAGIC) {
		/* Unfinished sequential-write blob */
		if (fdt_size_dt_struct(fdt) == 0)
			return -FDT_ERR_BADSTATE;
	} else {
		return -FDT_ERR_BADMAGIC;
	}

	return 0;
}