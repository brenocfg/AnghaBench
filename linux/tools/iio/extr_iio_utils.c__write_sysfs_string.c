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
 int fscanf (int /*<<< orphan*/ *,char*,char*) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int sprintf (char*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int _write_sysfs_string(const char *filename, const char *basedir,
			       const char *val, int verify)
{
	int ret = 0;
	FILE  *sysfsfp;
	char *temp = malloc(strlen(basedir) + strlen(filename) + 2);

	if (!temp) {
		fprintf(stderr, "Memory allocation failed\n");
		return -ENOMEM;
	}

	ret = sprintf(temp, "%s/%s", basedir, filename);
	if (ret < 0)
		goto error_free;

	sysfsfp = fopen(temp, "w");
	if (!sysfsfp) {
		ret = -errno;
		fprintf(stderr, "Could not open %s\n", temp);
		goto error_free;
	}

	ret = fprintf(sysfsfp, "%s", val);
	if (ret < 0) {
		if (fclose(sysfsfp))
			perror("_write_sysfs_string(): Failed to close dir");

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
			fprintf(stderr, "Could not open file to verify\n");
			goto error_free;
		}

		if (fscanf(sysfsfp, "%s", temp) != 1) {
			ret = errno ? -errno : -ENODATA;
			if (fclose(sysfsfp))
				perror("_write_sysfs_string(): Failed to close dir");

			goto error_free;
		}

		if (fclose(sysfsfp)) {
			ret = -errno;
			goto error_free;
		}

		if (strcmp(temp, val) != 0) {
			fprintf(stderr,
				"Possible failure in string write of %s "
				"Should be %s written to %s/%s\n", temp, val,
				basedir, filename);
			ret = -1;
		}
	}

error_free:
	free(temp);

	return ret;
}