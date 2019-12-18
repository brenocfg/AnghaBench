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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int FDT_ERR_BADOFFSET ; 
 int FDT_ERR_INTERNAL ; 
 int FDT_ERR_TRUNCATED ; 
 scalar_t__ FDT_MAGIC ; 
 scalar_t__ FDT_SW_MAGIC ; 
 scalar_t__ fdt_magic (void const*) ; 
 scalar_t__ fdt_off_dt_strings (void const*) ; 
 int fdt_ro_probe_ (void const*) ; 
 int fdt_size_dt_strings (void const*) ; 
 scalar_t__ fdt_totalsize (void const*) ; 
 int fdt_version (void const*) ; 
 char* memchr (char const*,char,size_t) ; 

const char *fdt_get_string(const void *fdt, int stroffset, int *lenp)
{
	uint32_t absoffset = stroffset + fdt_off_dt_strings(fdt);
	size_t len;
	int err;
	const char *s, *n;

	err = fdt_ro_probe_(fdt);
	if (err != 0)
		goto fail;

	err = -FDT_ERR_BADOFFSET;
	if (absoffset >= fdt_totalsize(fdt))
		goto fail;
	len = fdt_totalsize(fdt) - absoffset;

	if (fdt_magic(fdt) == FDT_MAGIC) {
		if (stroffset < 0)
			goto fail;
		if (fdt_version(fdt) >= 17) {
			if (stroffset >= fdt_size_dt_strings(fdt))
				goto fail;
			if ((fdt_size_dt_strings(fdt) - stroffset) < len)
				len = fdt_size_dt_strings(fdt) - stroffset;
		}
	} else if (fdt_magic(fdt) == FDT_SW_MAGIC) {
		if ((stroffset >= 0)
		    || (stroffset < -fdt_size_dt_strings(fdt)))
			goto fail;
		if ((-stroffset) < len)
			len = -stroffset;
	} else {
		err = -FDT_ERR_INTERNAL;
		goto fail;
	}

	s = (const char *)fdt + absoffset;
	n = memchr(s, '\0', len);
	if (!n) {
		/* missing terminating NULL */
		err = -FDT_ERR_TRUNCATED;
		goto fail;
	}

	if (lenp)
		*lenp = n - s;
	return s;

fail:
	if (lenp)
		*lenp = err;
	return NULL;
}