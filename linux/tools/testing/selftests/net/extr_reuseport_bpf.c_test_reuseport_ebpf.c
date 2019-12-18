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
struct test_params {int recv_socks; int send_port_min; } ;

/* Variables and functions */
 int /*<<< orphan*/  attach_ebpf (int,int) ; 
 int /*<<< orphan*/  build_recv_group (struct test_params,int*,int,int /*<<< orphan*/  (*) (int,int)) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_recv_order (struct test_params,int*,int) ; 

__attribute__((used)) static void test_reuseport_ebpf(struct test_params p)
{
	int i, fd[p.recv_socks];

	fprintf(stderr, "Testing EBPF mod %zd...\n", p.recv_socks);
	build_recv_group(p, fd, p.recv_socks, attach_ebpf);
	test_recv_order(p, fd, p.recv_socks);

	p.send_port_min += p.recv_socks * 2;
	fprintf(stderr, "Reprograming, testing mod %zd...\n", p.recv_socks / 2);
	attach_ebpf(fd[0], p.recv_socks / 2);
	test_recv_order(p, fd, p.recv_socks / 2);

	for (i = 0; i < p.recv_socks; ++i)
		close(fd[i]);
}