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
typedef  int /*<<< orphan*/  new_msr ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int debug ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,unsigned long long) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int pwrite (int,unsigned long long*,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

int put_msr(int cpu, int offset, unsigned long long new_msr)
{
	char pathname[32];
	int retval;
	int fd;

	sprintf(pathname, "/dev/cpu/%d/msr", cpu);
	fd = open(pathname, O_RDWR);
	if (fd < 0)
		err(-1, "%s open failed, try chown or chmod +r /dev/cpu/*/msr, or run as root", pathname);

	retval = pwrite(fd, &new_msr, sizeof(new_msr), offset);
	if (retval != sizeof(new_msr))
		err(-2, "pwrite(cpu%d, offset 0x%x, 0x%llx) = %d", cpu, offset, new_msr, retval);

	close(fd);

	if (debug > 1)
		fprintf(stderr, "put_msr(cpu%d, 0x%X, 0x%llX)\n", cpu, offset, new_msr);

	return 0;
}