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
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  close (int) ; 
 int lseek (int,unsigned int,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,unsigned long long*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int read_msr(int cpu, unsigned int idx, unsigned long long *val)
{
	int fd;
	char msr_file_name[64];

	sprintf(msr_file_name, "/dev/cpu/%d/msr", cpu);
	fd = open(msr_file_name, O_RDONLY);
	if (fd < 0)
		return -1;
	if (lseek(fd, idx, SEEK_CUR) == -1)
		goto err;
	if (read(fd, val, sizeof *val) != sizeof *val)
		goto err;
	close(fd);
	return 0;
 err:
	close(fd);
	return -1;
}