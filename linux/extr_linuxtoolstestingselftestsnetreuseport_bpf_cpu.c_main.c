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
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  stderr ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test (int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(void)
{
	int *rcv_fd, cpus;

	cpus = sysconf(_SC_NPROCESSORS_ONLN);
	if (cpus <= 0)
		error(1, errno, "failed counting cpus");

	rcv_fd = calloc(cpus, sizeof(int));
	if (!rcv_fd)
		error(1, 0, "failed to allocate array");

	fprintf(stderr, "---- IPv4 UDP ----\n");
	test(rcv_fd, cpus, AF_INET, SOCK_DGRAM);

	fprintf(stderr, "---- IPv6 UDP ----\n");
	test(rcv_fd, cpus, AF_INET6, SOCK_DGRAM);

	fprintf(stderr, "---- IPv4 TCP ----\n");
	test(rcv_fd, cpus, AF_INET, SOCK_STREAM);

	fprintf(stderr, "---- IPv6 TCP ----\n");
	test(rcv_fd, cpus, AF_INET6, SOCK_STREAM);

	free(rcv_fd);

	fprintf(stderr, "SUCCESS\n");
	return 0;
}