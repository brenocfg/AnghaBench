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
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEPORT ; 
 int /*<<< orphan*/  attach_cbpf (int,int) ; 
 int /*<<< orphan*/  attach_ebpf (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void test_filter_without_bind(void)
{
	int fd1, fd2, opt = 1;

	fprintf(stderr, "Testing filter add without bind...\n");
	fd1 = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd1 < 0)
		error(1, errno, "failed to create socket 1");
	fd2 = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd2 < 0)
		error(1, errno, "failed to create socket 2");
	if (setsockopt(fd1, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)))
		error(1, errno, "failed to set SO_REUSEPORT on socket 1");
	if (setsockopt(fd2, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)))
		error(1, errno, "failed to set SO_REUSEPORT on socket 2");

	attach_ebpf(fd1, 10);
	attach_cbpf(fd2, 10);

	close(fd1);
	close(fd2);
}