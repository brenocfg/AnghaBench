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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int*) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int sprintf (char*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char const*) ; 

int read_sysfs_posint(const char *filename, const char *basedir)
{
	int ret;
	FILE  *sysfsfp;
	char *temp = malloc(strlen(basedir) + strlen(filename) + 2);

	if (!temp) {
		fprintf(stderr, "Memory allocation failed");
		return -ENOMEM;
	}

	ret = sprintf(temp, "%s/%s", basedir, filename);
	if (ret < 0)
		goto error_free;

	sysfsfp = fopen(temp, "r");
	if (!sysfsfp) {
		ret = -errno;
		goto error_free;
	}

	errno = 0;
	if (fscanf(sysfsfp, "%d\n", &ret) != 1) {
		ret = errno ? -errno : -ENODATA;
		if (fclose(sysfsfp))
			perror("read_sysfs_posint(): Failed to close dir");

		goto error_free;
	}

	if (fclose(sysfsfp))
		ret = -errno;

error_free:
	free(temp);

	return ret;
}