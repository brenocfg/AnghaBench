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
struct fdt_property {void* data; void* len; void* nameoff; void* tag; } ;

/* Variables and functions */
 int FDT_CREATE_FLAG_NO_NAME_DEDUP ; 
 int FDT_ERR_NOSPACE ; 
 int FDT_PROP ; 
 int /*<<< orphan*/  FDT_SW_PROBE_STRUCT (void*) ; 
 scalar_t__ FDT_TAGALIGN (int) ; 
 void* cpu_to_fdt32 (int) ; 
 int fdt_add_string_ (void*,char const*) ; 
 int /*<<< orphan*/  fdt_del_last_string_ (void*,char const*) ; 
 int fdt_find_add_string_ (void*,char const*,int*) ; 
 struct fdt_property* fdt_grab_space_ (void*,scalar_t__) ; 
 int sw_flags (void*) ; 

int fdt_property_placeholder(void *fdt, const char *name, int len, void **valp)
{
	struct fdt_property *prop;
	int nameoff;
	int allocated;

	FDT_SW_PROBE_STRUCT(fdt);

	/* String de-duplication can be slow, _NO_NAME_DEDUP skips it */
	if (sw_flags(fdt) & FDT_CREATE_FLAG_NO_NAME_DEDUP) {
		allocated = 1;
		nameoff = fdt_add_string_(fdt, name);
	} else {
		nameoff = fdt_find_add_string_(fdt, name, &allocated);
	}
	if (nameoff == 0)
		return -FDT_ERR_NOSPACE;

	prop = fdt_grab_space_(fdt, sizeof(*prop) + FDT_TAGALIGN(len));
	if (! prop) {
		if (allocated)
			fdt_del_last_string_(fdt, name);
		return -FDT_ERR_NOSPACE;
	}

	prop->tag = cpu_to_fdt32(FDT_PROP);
	prop->nameoff = cpu_to_fdt32(nameoff);
	prop->len = cpu_to_fdt32(len);
	*valp = prop->data;
	return 0;
}