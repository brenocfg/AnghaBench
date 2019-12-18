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
 int /*<<< orphan*/  O_WRONLY ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 
 int write (int,char*,int) ; 

int write_debugfs_file(char *debugfs_file, int result)
{
	int rc = -1, fd;
	char path[PATH_MAX];
	char value[16];

	strcpy(path, "/sys/kernel/debug/");
	strncat(path, debugfs_file, PATH_MAX - strlen(path) - 1);

	if ((fd = open(path, O_WRONLY)) < 0)
		return rc;

	snprintf(value, 16, "%d", result);

	if ((rc = write(fd, value, strlen(value))) < 0)
		return rc;

	close(fd);

	return 0;
}