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
struct sock_addr_test {char* descr; int (* loadfn ) (struct sock_addr_test const*) ;scalar_t__ expected_result; int /*<<< orphan*/  attach_type; } ;

/* Variables and functions */
 scalar_t__ ATTACH_OKAY ; 
 scalar_t__ ATTACH_REJECT ; 
#define  BPF_CGROUP_INET4_BIND 135 
#define  BPF_CGROUP_INET4_CONNECT 134 
#define  BPF_CGROUP_INET6_BIND 133 
#define  BPF_CGROUP_INET6_CONNECT 132 
#define  BPF_CGROUP_UDP4_RECVMSG 131 
#define  BPF_CGROUP_UDP4_SENDMSG 130 
#define  BPF_CGROUP_UDP6_RECVMSG 129 
#define  BPF_CGROUP_UDP6_SENDMSG 128 
 int /*<<< orphan*/  BPF_F_ALLOW_OVERRIDE ; 
 int ENOTSUPP ; 
 int EPERM ; 
 scalar_t__ LOAD_REJECT ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ SYSCALL_ENOTSUPP ; 
 scalar_t__ SYSCALL_EPERM ; 
 int bpf_prog_attach (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_detach (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int run_bind_test_case (struct sock_addr_test const*) ; 
 int run_connect_test_case (struct sock_addr_test const*) ; 
 int run_xmsg_test_case (struct sock_addr_test const*,int) ; 
 int stub1 (struct sock_addr_test const*) ; 

__attribute__((used)) static int run_test_case(int cgfd, const struct sock_addr_test *test)
{
	int progfd = -1;
	int err = 0;

	printf("Test case: %s .. ", test->descr);

	progfd = test->loadfn(test);
	if (test->expected_result == LOAD_REJECT && progfd < 0)
		goto out;
	else if (test->expected_result == LOAD_REJECT || progfd < 0)
		goto err;

	err = bpf_prog_attach(progfd, cgfd, test->attach_type,
			      BPF_F_ALLOW_OVERRIDE);
	if (test->expected_result == ATTACH_REJECT && err) {
		err = 0; /* error was expected, reset it */
		goto out;
	} else if (test->expected_result == ATTACH_REJECT || err) {
		goto err;
	} else if (test->expected_result == ATTACH_OKAY) {
		err = 0;
		goto out;
	}

	switch (test->attach_type) {
	case BPF_CGROUP_INET4_BIND:
	case BPF_CGROUP_INET6_BIND:
		err = run_bind_test_case(test);
		break;
	case BPF_CGROUP_INET4_CONNECT:
	case BPF_CGROUP_INET6_CONNECT:
		err = run_connect_test_case(test);
		break;
	case BPF_CGROUP_UDP4_SENDMSG:
	case BPF_CGROUP_UDP6_SENDMSG:
		err = run_xmsg_test_case(test, 1);
		break;
	case BPF_CGROUP_UDP4_RECVMSG:
	case BPF_CGROUP_UDP6_RECVMSG:
		err = run_xmsg_test_case(test, 0);
		break;
	default:
		goto err;
	}

	if (test->expected_result == SYSCALL_EPERM && err == EPERM) {
		err = 0; /* error was expected, reset it */
		goto out;
	}

	if (test->expected_result == SYSCALL_ENOTSUPP && err == ENOTSUPP) {
		err = 0; /* error was expected, reset it */
		goto out;
	}

	if (err || test->expected_result != SUCCESS)
		goto err;

	goto out;
err:
	err = -1;
out:
	/* Detaching w/o checking return code: best effort attempt. */
	if (progfd != -1)
		bpf_prog_detach(cgfd, test->attach_type);
	close(progfd);
	printf("[%s]\n", err ? "FAIL" : "PASS");
	return err;
}