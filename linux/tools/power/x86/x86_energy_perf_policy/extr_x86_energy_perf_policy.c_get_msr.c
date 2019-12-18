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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int debug ; 
 int /*<<< orphan*/  err (int,char*,char*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,unsigned long long) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int pread (int,unsigned long long*,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

int get_msr(int cpu, int offset, unsigned long long *msr)
{
	int retval;
	char pathname[32];
	int fd;

	sprintf(pathname, "/dev/cpu/%d/msr", cpu);
	fd = open(pathname, O_RDONLY);
	if (fd < 0)
		err(-1, "%s open failed, try chown or chmod +r /dev/cpu/*/msr, or run as root", pathname);

	retval = pread(fd, msr, sizeof(*msr), offset);
	if (retval != sizeof(*msr))
		err(-1, "%s offset 0x%llx read failed", pathname, (unsigned long long)offset);

	if (debug > 1)
		fprintf(stderr, "get_msr(cpu%d, 0x%X, 0x%llX)\n", cpu, offset, *msr);

	close(fd);
	return 0;
}