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
 int /*<<< orphan*/  O_RDWR ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,char*,int) ; 
 int snprintf (char*,int,char*,int) ; 
 scalar_t__ write (int,char*,int) ; 

void enable_fastopen(void)
{
	int fd = open("/proc/sys/net/ipv4/tcp_fastopen", 0);
	int rw_mask = 3;  /* bit 1: client side; bit-2 server side */
	int val, size;
	char buf[16];

	if (fd < 0)
		error(1, errno, "Unable to open tcp_fastopen sysctl");
	if (read(fd, buf, sizeof(buf)) <= 0)
		error(1, errno, "Unable to read tcp_fastopen sysctl");
	val = atoi(buf);
	close(fd);

	if ((val & rw_mask) != rw_mask) {
		fd = open("/proc/sys/net/ipv4/tcp_fastopen", O_RDWR);
		if (fd < 0)
			error(1, errno,
			      "Unable to open tcp_fastopen sysctl for writing");
		val |= rw_mask;
		size = snprintf(buf, 16, "%d", val);
		if (write(fd, buf, size) <= 0)
			error(1, errno, "Unable to write tcp_fastopen sysctl");
		close(fd);
	}
}