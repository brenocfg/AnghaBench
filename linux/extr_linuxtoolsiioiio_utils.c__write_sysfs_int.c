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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ENODATA ; 
 int ENOMEM ; 
 int errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int*) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int sprintf (char*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int _write_sysfs_int(const char *filename, const char *basedir, int val,
			    int verify)
{
	int ret = 0;
	FILE *sysfsfp;
	int test;
	char *temp = malloc(strlen(basedir) + strlen(filename) + 2);

	if (!temp)
		return -ENOMEM;

	ret = sprintf(temp, "%s/%s", basedir, filename);
	if (ret < 0)
		goto error_free;

	sysfsfp = fopen(temp, "w");
	if (!sysfsfp) {
		ret = -errno;
		fprintf(stderr, "failed to open %s\n", temp);
		goto error_free;
	}

	ret = fprintf(sysfsfp, "%d", val);
	if (ret < 0) {
		if (fclose(sysfsfp))
			perror("_write_sysfs_int(): Failed to close dir");

		goto error_free;
	}

	if (fclose(sysfsfp)) {
		ret = -errno;
		goto error_free;
	}

	if (verify) {
		sysfsfp = fopen(temp, "r");
		if (!sysfsfp) {
			ret = -errno;
			fprintf(stderr, "failed to open %s\n", temp);
			goto error_free;
		}

		if (fscanf(sysfsfp, "%d", &test) != 1) {
			ret = errno ? -errno : -ENODATA;
			if (fclose(sysfsfp))
				perror("_write_sysfs_int(): Failed to close dir");

			goto error_free;
		}

		if (fclose(sysfsfp)) {
			ret = -errno;
			goto error_free;
		}

		if (test != val) {
			fprintf(stderr,
				"Possible failure in int write %d to %s/%s\n",
				val, basedir, filename);
			ret = -1;
		}
	}

error_free:
	free(temp);
	return ret;
}