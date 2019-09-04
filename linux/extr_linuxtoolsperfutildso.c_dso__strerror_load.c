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
struct dso {int load_errno; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int __DSO_LOAD_ERRNO__END ; 
 int __DSO_LOAD_ERRNO__START ; 
 int /*<<< orphan*/  scnprintf (char*,size_t,char*,char const*) ; 
 char* str_error_r (int,char*,size_t) ; 

int dso__strerror_load(struct dso *dso, char *buf, size_t buflen)
{
	int idx, errnum = dso->load_errno;
	/*
	 * This must have a same ordering as the enum dso_load_errno.
	 */
	static const char *dso_load__error_str[] = {
	"Internal tools/perf/ library error",
	"Invalid ELF file",
	"Can not read build id",
	"Mismatching build id",
	"Decompression failure",
	};

	BUG_ON(buflen == 0);

	if (errnum >= 0) {
		const char *err = str_error_r(errnum, buf, buflen);

		if (err != buf)
			scnprintf(buf, buflen, "%s", err);

		return 0;
	}

	if (errnum <  __DSO_LOAD_ERRNO__START || errnum >= __DSO_LOAD_ERRNO__END)
		return -1;

	idx = errnum - __DSO_LOAD_ERRNO__START;
	scnprintf(buf, buflen, "%s", dso_load__error_str[idx]);
	return 0;
}