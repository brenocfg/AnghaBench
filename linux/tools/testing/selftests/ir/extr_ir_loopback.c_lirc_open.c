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
struct dirent {char const* d_name; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int DNAME_PATH_MAX ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int SYSFS_PATH_MAX ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,char*) ; 
 int /*<<< orphan*/  ksft_exit_skip (char*,char const*) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

int lirc_open(const char *rc)
{
	struct dirent *dent;
	char buf[SYSFS_PATH_MAX + DNAME_PATH_MAX];
	DIR *d;
	int fd;

	snprintf(buf, sizeof(buf), "/sys/class/rc/%s", rc);

	d = opendir(buf);
	if (!d)
		ksft_exit_fail_msg("cannot open %s: %m\n", buf);

	while ((dent = readdir(d)) != NULL) {
		if (!strncmp(dent->d_name, "lirc", 4)) {
			snprintf(buf, sizeof(buf), "/dev/%s", dent->d_name);
			break;
		}
	}

	if (!dent)
		ksft_exit_skip("cannot find lirc device for %s\n", rc);

	closedir(d);

	fd = open(buf, O_RDWR | O_NONBLOCK);
	if (fd == -1)
		ksft_exit_fail_msg("cannot open: %s: %m\n", buf);

	return fd;
}