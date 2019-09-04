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
struct sock_fprog {unsigned short len; struct sock_filter* filter; } ;
struct sock_filter {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (struct sock_filter*) ; 
 int BPF_K ; 
 int BPF_RET ; 
 struct sock_filter BPF_STMT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLOCK_PROCESS_CPUTIME_ID ; 
 int /*<<< orphan*/  PR_SET_NO_NEW_PRIVS ; 
 int /*<<< orphan*/  PR_SET_SECCOMP ; 
 int /*<<< orphan*/  SECCOMP_MODE_FILTER ; 
 int /*<<< orphan*/  SECCOMP_RET_ALLOW ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned long long calibrate () ; 
 long prctl (int /*<<< orphan*/ ,int,struct sock_fprog*,...) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 unsigned long long strtoull (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long long timing (int /*<<< orphan*/ ,unsigned long long) ; 

int main(int argc, char *argv[])
{
	struct sock_filter filter[] = {
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	};
	struct sock_fprog prog = {
		.len = (unsigned short)ARRAY_SIZE(filter),
		.filter = filter,
	};
	long ret;
	unsigned long long samples;
	unsigned long long native, filtered;

	if (argc > 1)
		samples = strtoull(argv[1], NULL, 0);
	else
		samples = calibrate();

	printf("Benchmarking %llu samples...\n", samples);

	native = timing(CLOCK_PROCESS_CPUTIME_ID, samples) / samples;
	printf("getpid native: %llu ns\n", native);

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	assert(ret == 0);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog);
	assert(ret == 0);

	filtered = timing(CLOCK_PROCESS_CPUTIME_ID, samples) / samples;
	printf("getpid RET_ALLOW: %llu ns\n", filtered);

	printf("Estimated seccomp overhead per syscall: %llu ns\n",
		filtered - native);

	if (filtered == native)
		printf("Trying running again with more samples.\n");

	return 0;
}