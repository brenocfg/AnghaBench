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
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ errno ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 

int main(void)
{
	char buf[64];
	int fd;

	fd = open("/proc/self/wchan", O_RDONLY);
	if (fd == -1) {
		if (errno == ENOENT)
			return 4;
		return 1;
	}

	buf[0] = '\0';
	if (read(fd, buf, sizeof(buf)) != 1)
		return 1;
	if (buf[0] != '0')
		return 1;
	return 0;
}