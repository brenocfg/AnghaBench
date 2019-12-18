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
 int O_APPEND ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_WRONLY ; 
 int errno ; 
 int open64 (char*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

int open_file(char *path, int r, int w, int append)
{
	int mode = 0, fd;

	if (r && !w)
		mode = O_RDONLY;
	else if (!r && w)
		mode = O_WRONLY;
	else if (r && w)
		mode = O_RDWR;
	else panic("Impossible mode in open_file");

	if (append)
		mode |= O_APPEND;
	fd = open64(path, mode);
	if (fd < 0)
		return -errno;
	else return fd;
}