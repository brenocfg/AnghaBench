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

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ isdigit (char) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_err (char*) ; 
 long read (int,char*,int) ; 
 int sscanf (char*,char*,unsigned int*,...) ; 
 char* strchr (char*,char) ; 

unsigned int get_possible_cpus(void)
{
	static unsigned int result;
	char buf[128];
	long int n;
	char *ptr;
	int fd;

	if (result)
		return result;

	fd = open("/sys/devices/system/cpu/possible", O_RDONLY);
	if (fd < 0) {
		p_err("can't open sysfs possible cpus");
		exit(-1);
	}

	n = read(fd, buf, sizeof(buf));
	if (n < 2) {
		p_err("can't read sysfs possible cpus");
		exit(-1);
	}
	close(fd);

	if (n == sizeof(buf)) {
		p_err("read sysfs possible cpus overflow");
		exit(-1);
	}

	ptr = buf;
	n = 0;
	while (*ptr && *ptr != '\n') {
		unsigned int a, b;

		if (sscanf(ptr, "%u-%u", &a, &b) == 2) {
			n += b - a + 1;

			ptr = strchr(ptr, '-') + 1;
		} else if (sscanf(ptr, "%u", &a) == 1) {
			n++;
		} else {
			assert(0);
		}

		while (isdigit(*ptr))
			ptr++;
		if (*ptr == ',')
			ptr++;
	}

	result = n;

	return result;
}