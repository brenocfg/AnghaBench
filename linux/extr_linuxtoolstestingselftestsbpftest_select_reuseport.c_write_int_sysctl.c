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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int,char*,char*,char const*,int,int,...) ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,int) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void write_int_sysctl(const char *sysctl, int v)
{
	int fd, ret, size;
	char buf[16];

	fd = open(sysctl, O_RDWR);
	CHECK(fd == -1, "open(sysctl)", "sysctl:%s fd:%d errno:%d\n",
	      sysctl, fd, errno);

	size = snprintf(buf, sizeof(buf), "%d", v);
	ret = write(fd, buf, size);
	CHECK(ret != size, "write(sysctl)",
	      "sysctl:%s ret:%d size:%d errno:%d\n", sysctl, ret, size, errno);
	close(fd);
}