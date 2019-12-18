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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EIO ; 
 int EOF ; 
 int STRERR_BUFSIZE ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char const*,int*) ; 
 int /*<<< orphan*/  libbpf_strerror_r (int,char*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_uint_from_file(const char *file, const char *fmt)
{
	char buf[STRERR_BUFSIZE];
	int err, ret;
	FILE *f;

	f = fopen(file, "r");
	if (!f) {
		err = -errno;
		pr_debug("failed to open '%s': %s\n", file,
			 libbpf_strerror_r(err, buf, sizeof(buf)));
		return err;
	}
	err = fscanf(f, fmt, &ret);
	if (err != 1) {
		err = err == EOF ? -EIO : -errno;
		pr_debug("failed to parse '%s': %s\n", file,
			libbpf_strerror_r(err, buf, sizeof(buf)));
		fclose(f);
		return err;
	}
	fclose(f);
	return ret;
}