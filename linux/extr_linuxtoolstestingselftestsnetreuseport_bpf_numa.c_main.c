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
 int* calloc (int,int) ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  ksft_exit_skip (char*) ; 
 scalar_t__ numa_available () ; 
 int numa_max_node () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test (int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(void)
{
	int *rcv_fd, nodes;

	if (numa_available() < 0)
		ksft_exit_skip("no numa api support\n");

	nodes = numa_max_node() + 1;

	rcv_fd = calloc(nodes, sizeof(int));
	if (!rcv_fd)
		error(1, 0, "failed to allocate array");

	fprintf(stderr, "---- IPv4 UDP ----\n");
	test(rcv_fd, nodes, AF_INET, SOCK_DGRAM);

	fprintf(stderr, "---- IPv6 UDP ----\n");
	test(rcv_fd, nodes, AF_INET6, SOCK_DGRAM);

	fprintf(stderr, "---- IPv4 TCP ----\n");
	test(rcv_fd, nodes, AF_INET, SOCK_STREAM);

	fprintf(stderr, "---- IPv6 TCP ----\n");
	test(rcv_fd, nodes, AF_INET6, SOCK_STREAM);

	free(rcv_fd);

	fprintf(stderr, "SUCCESS\n");
	return 0;
}