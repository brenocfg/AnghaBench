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
struct fdt_property {scalar_t__ data; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDT_RW_CHECK_HEADER (void*) ; 
 int /*<<< orphan*/  FDT_TAGALIGN (int) ; 
 int /*<<< orphan*/  cpu_to_fdt32 (int) ; 
 int fdt_add_property_ (void*,int,char const*,int,struct fdt_property**) ; 
 struct fdt_property* fdt_get_property_w (void*,int,char const*,int*) ; 
 int fdt_splice_struct_ (void*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,int) ; 

int fdt_appendprop(void *fdt, int nodeoffset, const char *name,
		   const void *val, int len)
{
	struct fdt_property *prop;
	int err, oldlen, newlen;

	FDT_RW_CHECK_HEADER(fdt);

	prop = fdt_get_property_w(fdt, nodeoffset, name, &oldlen);
	if (prop) {
		newlen = len + oldlen;
		err = fdt_splice_struct_(fdt, prop->data,
					 FDT_TAGALIGN(oldlen),
					 FDT_TAGALIGN(newlen));
		if (err)
			return err;
		prop->len = cpu_to_fdt32(newlen);
		memcpy(prop->data + oldlen, val, len);
	} else {
		err = fdt_add_property_(fdt, nodeoffset, name, len, &prop);
		if (err)
			return err;
		memcpy(prop->data, val, len);
	}
	return 0;
}