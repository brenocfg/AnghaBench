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
struct stat {scalar_t__ st_dev; scalar_t__ st_ino; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  assert (int) ; 
 int fstat (int,struct stat*) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int main(void)
{
	int fd0, fd1, fd2;
	struct stat st0, st1, st2;
	char buf[64];
	int rv;

	fd0 = open("/", O_DIRECTORY|O_RDONLY);
	assert(fd0 >= 0);

	snprintf(buf, sizeof(buf), "/proc/self/fd/%u", fd0);
	fd1 = open(buf, O_RDONLY);
	assert(fd1 >= 0);

	snprintf(buf, sizeof(buf), "/proc/thread-self/fd/%u", fd0);
	fd2 = open(buf, O_RDONLY);
	assert(fd2 >= 0);

	rv = fstat(fd0, &st0);
	assert(rv == 0);
	rv = fstat(fd1, &st1);
	assert(rv == 0);
	rv = fstat(fd2, &st2);
	assert(rv == 0);

	assert(st0.st_dev == st1.st_dev);
	assert(st0.st_ino == st1.st_ino);

	assert(st0.st_dev == st2.st_dev);
	assert(st0.st_ino == st2.st_ino);

	return 0;
}