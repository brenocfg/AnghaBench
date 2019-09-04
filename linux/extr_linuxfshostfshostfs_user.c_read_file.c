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
 int errno ; 
 int pread64 (int,char*,int,unsigned long long) ; 

int read_file(int fd, unsigned long long *offset, char *buf, int len)
{
	int n;

	n = pread64(fd, buf, len, *offset);
	if (n < 0)
		return -errno;
	*offset += n;
	return n;
}