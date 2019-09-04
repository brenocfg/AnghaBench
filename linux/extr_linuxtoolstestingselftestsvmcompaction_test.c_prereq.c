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
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int read (int,char*,int) ; 

int prereq(void)
{
	char allowed;
	int fd;

	fd = open("/proc/sys/vm/compact_unevictable_allowed",
		  O_RDONLY | O_NONBLOCK);
	if (fd < 0) {
		perror("Failed to open\n"
		       "/proc/sys/vm/compact_unevictable_allowed\n");
		return -1;
	}

	if (read(fd, &allowed, sizeof(char)) != sizeof(char)) {
		perror("Failed to read from\n"
		       "/proc/sys/vm/compact_unevictable_allowed\n");
		close(fd);
		return -1;
	}

	close(fd);
	if (allowed == '1')
		return 0;

	return -1;
}