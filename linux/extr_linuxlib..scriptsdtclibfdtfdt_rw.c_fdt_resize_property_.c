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
struct fdt_property {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDT_TAGALIGN (int) ; 
 int /*<<< orphan*/  cpu_to_fdt32 (int) ; 
 struct fdt_property* fdt_get_property_w (void*,int,char const*,int*) ; 
 int fdt_splice_struct_ (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fdt_resize_property_(void *fdt, int nodeoffset, const char *name,
				int len, struct fdt_property **prop)
{
	int oldlen;
	int err;

	*prop = fdt_get_property_w(fdt, nodeoffset, name, &oldlen);
	if (!*prop)
		return oldlen;

	if ((err = fdt_splice_struct_(fdt, (*prop)->data, FDT_TAGALIGN(oldlen),
				      FDT_TAGALIGN(len))))
		return err;

	(*prop)->len = cpu_to_fdt32(len);
	return 0;
}