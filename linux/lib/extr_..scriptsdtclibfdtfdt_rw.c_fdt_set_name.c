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
 int /*<<< orphan*/  FDT_RW_PROBE (void*) ; 
 int /*<<< orphan*/  FDT_TAGALIGN (int) ; 
 scalar_t__ fdt_get_name (void*,int,int*) ; 
 int fdt_splice_struct_ (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

int fdt_set_name(void *fdt, int nodeoffset, const char *name)
{
	char *namep;
	int oldlen, newlen;
	int err;

	FDT_RW_PROBE(fdt);

	namep = (char *)(uintptr_t)fdt_get_name(fdt, nodeoffset, &oldlen);
	if (!namep)
		return oldlen;

	newlen = strlen(name);

	err = fdt_splice_struct_(fdt, namep, FDT_TAGALIGN(oldlen+1),
				 FDT_TAGALIGN(newlen+1));
	if (err)
		return err;

	memcpy(namep, name, newlen+1);
	return 0;
}