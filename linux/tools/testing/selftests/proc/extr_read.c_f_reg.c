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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dirfd (int /*<<< orphan*/ *) ; 
 int openat (int /*<<< orphan*/ ,char const*,int) ; 
 int read (int,char*,int) ; 

__attribute__((used)) static void f_reg(DIR *d, const char *filename)
{
	char buf[4096];
	int fd;
	ssize_t rv;

	/* read from /proc/kmsg can block */
	fd = openat(dirfd(d), filename, O_RDONLY|O_NONBLOCK);
	if (fd == -1)
		return;
	rv = read(fd, buf, sizeof(buf));
	assert((0 <= rv && rv <= sizeof(buf)) || rv == -1);
	close(fd);
}