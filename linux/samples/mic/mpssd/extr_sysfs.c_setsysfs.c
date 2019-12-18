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
 char* MICSYSFSDIR ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mpsslog (char*,char*,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 char* readsysfs (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ write (int,char*,int /*<<< orphan*/ ) ; 

int
setsysfs(char *dir, char *entry, char *value)
{
	char filename[PATH_MAX];
	char *oldvalue;
	int fd, ret = 0;

	if (dir == NULL)
		snprintf(filename, PATH_MAX, "%s/%s", MICSYSFSDIR, entry);
	else
		snprintf(filename, PATH_MAX, "%s/%s/%s",
			 MICSYSFSDIR, dir, entry);

	oldvalue = readsysfs(dir, entry);

	fd = open(filename, O_RDWR);
	if (fd < 0) {
		ret = errno;
		mpsslog("Failed to open sysfs entry '%s': %s\n",
			filename, strerror(errno));
		goto done;
	}

	if (!oldvalue || strcmp(value, oldvalue)) {
		if (write(fd, value, strlen(value)) < 0) {
			ret = errno;
			mpsslog("Failed to write new sysfs entry '%s': %s\n",
				filename, strerror(errno));
		}
	}
	close(fd);
done:
	if (oldvalue)
		free(oldvalue);
	return ret;
}