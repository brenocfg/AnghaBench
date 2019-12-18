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
 int /*<<< orphan*/  CHECK_PERROR_RET (int) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 char* PMU_TYPE_FILE ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int snprintf (char*,int,char*,char const*) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int bpf_find_probe_type(const char *event_type)
{
	char buf[256];
	int fd, ret;

	ret = snprintf(buf, sizeof(buf), PMU_TYPE_FILE, event_type);
	CHECK_PERROR_RET(ret < 0 || ret >= sizeof(buf));

	fd = open(buf, O_RDONLY);
	CHECK_PERROR_RET(fd < 0);

	ret = read(fd, buf, sizeof(buf));
	close(fd);
	CHECK_PERROR_RET(ret < 0 || ret >= sizeof(buf));

	errno = 0;
	ret = (int)strtol(buf, NULL, 10);
	CHECK_PERROR_RET(errno);
	return ret;
}