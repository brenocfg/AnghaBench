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
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dbg (char*,char const*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int write (int,char const*,size_t) ; 

int write_sysfs_attribute(const char *attr_path, const char *new_value,
			  size_t len)
{
	int fd;
	int length;

	fd = open(attr_path, O_WRONLY);
	if (fd < 0) {
		dbg("error opening attribute %s", attr_path);
		return -1;
	}

	length = write(fd, new_value, len);
	if (length < 0) {
		dbg("error writing to attribute %s", attr_path);
		close(fd);
		return -1;
	}

	close(fd);

	return 0;
}