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
 int /*<<< orphan*/  CHECK (int,char*,char*,char const*,int,int /*<<< orphan*/ ) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 

__attribute__((used)) static int read_int_sysctl(const char *sysctl)
{
	char buf[16];
	int fd, ret;

	fd = open(sysctl, 0);
	CHECK(fd == -1, "open(sysctl)", "sysctl:%s fd:%d errno:%d\n",
	      sysctl, fd, errno);

	ret = read(fd, buf, sizeof(buf));
	CHECK(ret <= 0, "read(sysctl)", "sysctl:%s ret:%d errno:%d\n",
	      sysctl, ret, errno);
	close(fd);

	return atoi(buf);
}