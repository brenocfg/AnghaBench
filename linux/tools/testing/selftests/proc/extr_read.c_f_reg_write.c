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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dirfd (int /*<<< orphan*/ *) ; 
 int openat (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 size_t write (int,char const*,size_t) ; 

__attribute__((used)) static void f_reg_write(DIR *d, const char *filename, const char *buf, size_t len)
{
	int fd;
	ssize_t rv;

	fd = openat(dirfd(d), filename, O_WRONLY);
	if (fd == -1)
		return;
	rv = write(fd, buf, len);
	assert((0 <= rv && rv <= len) || rv == -1);
	close(fd);
}