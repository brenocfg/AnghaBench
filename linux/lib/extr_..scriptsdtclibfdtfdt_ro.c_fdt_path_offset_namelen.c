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
 int FDT_ERR_BADPATH ; 
 int /*<<< orphan*/  FDT_RO_PROBE (void const*) ; 
 char* fdt_get_alias_namelen (void const*,char const*,int) ; 
 int fdt_path_offset (void const*,char const*) ; 
 int fdt_subnode_offset_namelen (void const*,int,char const*,int) ; 
 char* memchr (char const*,char,int) ; 

int fdt_path_offset_namelen(const void *fdt, const char *path, int namelen)
{
	const char *end = path + namelen;
	const char *p = path;
	int offset = 0;

	FDT_RO_PROBE(fdt);

	/* see if we have an alias */
	if (*path != '/') {
		const char *q = memchr(path, '/', end - p);

		if (!q)
			q = end;

		p = fdt_get_alias_namelen(fdt, p, q - p);
		if (!p)
			return -FDT_ERR_BADPATH;
		offset = fdt_path_offset(fdt, p);

		p = q;
	}

	while (p < end) {
		const char *q;

		while (*p == '/') {
			p++;
			if (p == end)
				return offset;
		}
		q = memchr(p, '/', end - p);
		if (! q)
			q = end;

		offset = fdt_subnode_offset_namelen(fdt, offset, p, q-p);
		if (offset < 0)
			return offset;

		p = q;
	}

	return offset;
}