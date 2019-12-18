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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf1 ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ SYS_read ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,long,long,long,long) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,scalar_t__) ; 
 scalar_t__ sys_read (int,char*,int) ; 

int main(void)
{
	char buf1[64];
	char buf2[64];
	int fd;
	ssize_t rv;

	fd = open("/proc/self/syscall", O_RDONLY);
	if (fd == -1) {
		if (errno == ENOENT)
			return 4;
		return 1;
	}

	/* Do direct system call as libc can wrap anything. */
	snprintf(buf1, sizeof(buf1), "%ld 0x%lx 0x%lx 0x%lx",
		 (long)SYS_read, (long)fd, (long)buf2, (long)sizeof(buf2));

	memset(buf2, 0, sizeof(buf2));
	rv = sys_read(fd, buf2, sizeof(buf2));
	if (rv < 0)
		return 1;
	if (rv < strlen(buf1))
		return 1;
	if (strncmp(buf1, buf2, strlen(buf1)) != 0)
		return 1;

	return 0;
}