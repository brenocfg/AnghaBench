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

/* Variables and functions */
#define  FDT_BEGIN_NODE 132 
#define  FDT_END 131 
#define  FDT_END_NODE 130 
 int FDT_ERR_BADSTRUCTURE ; 
 int FDT_ERR_INTERNAL ; 
 int FDT_ERR_TRUNCATED ; 
#define  FDT_NOP 129 
#define  FDT_PROP 128 
 size_t FDT_V1_SIZE ; 
 unsigned int INT_MAX ; 
 int fdt_check_header (void const*) ; 
 void* fdt_getprop_by_offset (void const*,int,char const**,int*) ; 
 int fdt_next_tag (void const*,int,int*) ; 
 int fdt_num_mem_rsv (void const*) ; 
 size_t fdt_totalsize (void const*) ; 

int fdt_check_full(const void *fdt, size_t bufsize)
{
	int err;
	int num_memrsv;
	int offset, nextoffset = 0;
	uint32_t tag;
	unsigned depth = 0;
	const void *prop;
	const char *propname;

	if (bufsize < FDT_V1_SIZE)
		return -FDT_ERR_TRUNCATED;
	err = fdt_check_header(fdt);
	if (err != 0)
		return err;
	if (bufsize < fdt_totalsize(fdt))
		return -FDT_ERR_TRUNCATED;

	num_memrsv = fdt_num_mem_rsv(fdt);
	if (num_memrsv < 0)
		return num_memrsv;

	while (1) {
		offset = nextoffset;
		tag = fdt_next_tag(fdt, offset, &nextoffset);

		if (nextoffset < 0)
			return nextoffset;

		switch (tag) {
		case FDT_NOP:
			break;

		case FDT_END:
			if (depth != 0)
				return -FDT_ERR_BADSTRUCTURE;
			return 0;

		case FDT_BEGIN_NODE:
			depth++;
			if (depth > INT_MAX)
				return -FDT_ERR_BADSTRUCTURE;
			break;

		case FDT_END_NODE:
			if (depth == 0)
				return -FDT_ERR_BADSTRUCTURE;
			depth--;
			break;

		case FDT_PROP:
			prop = fdt_getprop_by_offset(fdt, offset, &propname,
						     &err);
			if (!prop)
				return err;
			break;

		default:
			return -FDT_ERR_INTERNAL;
		}
	}
}