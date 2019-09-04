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
struct rlimit {scalar_t__ rlim_max; scalar_t__ rlim_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 scalar_t__ RLIM_INFINITY ; 
 int /*<<< orphan*/  getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 

__attribute__((used)) static  __attribute__((constructor)) void bpf_rlimit_ctor(void)
{
	struct rlimit rlim_old, rlim_new = {
		.rlim_cur	= RLIM_INFINITY,
		.rlim_max	= RLIM_INFINITY,
	};

	getrlimit(RLIMIT_MEMLOCK, &rlim_old);
	/* For the sake of running the test cases, we temporarily
	 * set rlimit to infinity in order for kernel to focus on
	 * errors from actual test cases and not getting noise
	 * from hitting memlock limits. The limit is on per-process
	 * basis and not a global one, hence destructor not really
	 * needed here.
	 */
	if (setrlimit(RLIMIT_MEMLOCK, &rlim_new) < 0) {
		perror("Unable to lift memlock rlimit");
		/* Trying out lower limit, but expect potential test
		 * case failures from this!
		 */
		rlim_new.rlim_cur = rlim_old.rlim_cur + (1UL << 20);
		rlim_new.rlim_max = rlim_old.rlim_max + (1UL << 20);
		setrlimit(RLIMIT_MEMLOCK, &rlim_new);
	}
}