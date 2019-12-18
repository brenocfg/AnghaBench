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
typedef  int /*<<< orphan*/  vendor_id_buf ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_err (char*,char*,...) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_sysfs_hex_int(char *path)
{
	char vendor_id_buf[8];
	int len;
	int fd;

	fd = open(path, O_RDONLY);
	if (fd < 0) {
		p_err("Can't open %s: %s", path, strerror(errno));
		return -1;
	}

	len = read(fd, vendor_id_buf, sizeof(vendor_id_buf));
	close(fd);
	if (len < 0) {
		p_err("Can't read %s: %s", path, strerror(errno));
		return -1;
	}
	if (len >= (int)sizeof(vendor_id_buf)) {
		p_err("Value in %s too long", path);
		return -1;
	}

	vendor_id_buf[len] = 0;

	return strtol(vendor_id_buf, NULL, 0);
}