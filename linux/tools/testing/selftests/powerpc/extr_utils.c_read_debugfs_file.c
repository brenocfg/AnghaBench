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
typedef  int /*<<< orphan*/  value ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int PATH_MAX ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 

int read_debugfs_file(char *debugfs_file, int *result)
{
	int rc = -1, fd;
	char path[PATH_MAX];
	char value[16];

	strcpy(path, "/sys/kernel/debug/");
	strncat(path, debugfs_file, PATH_MAX - strlen(path) - 1);

	if ((fd = open(path, O_RDONLY)) < 0)
		return rc;

	if ((rc = read(fd, value, sizeof(value))) < 0)
		return rc;

	value[15] = 0;
	*result = atoi(value);
	close(fd);

	return 0;
}