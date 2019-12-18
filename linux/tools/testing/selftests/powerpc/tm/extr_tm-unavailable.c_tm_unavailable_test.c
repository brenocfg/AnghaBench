#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
typedef  int /*<<< orphan*/  cpu_set_t ;
struct TYPE_2__ {scalar_t__ result; int exception; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int FP_UNA_EXCEPTION ; 
 int NUM_EXCEPTIONS ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int VEC_UNA_EXCEPTION ; 
 int /*<<< orphan*/  exit (int) ; 
 TYPE_1__ flags ; 
 int /*<<< orphan*/  have_htm () ; 
 int /*<<< orphan*/  pr_err (int,char*) ; 
 int /*<<< orphan*/  pr_warn (int,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int pthread_attr_init (int /*<<< orphan*/ *) ; 
 int pthread_attr_setaffinity_np (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pthread_setname_np (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_fp_vec (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tm_una_pong ; 

int tm_unavailable_test(void)
{
	int rc, exception; /* FP = 0, VEC = 1, VSX = 2 */
	pthread_t t1;
	pthread_attr_t attr;
	cpu_set_t cpuset;

	SKIP_IF(!have_htm());

	/* Set only CPU 0 in the mask. Both threads will be bound to CPU 0. */
	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);

	/* Init pthread attribute. */
	rc = pthread_attr_init(&attr);
	if (rc)
		pr_err(rc, "pthread_attr_init()");

	/* Set CPU 0 mask into the pthread attribute. */
	rc = pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset);
	if (rc)
		pr_err(rc, "pthread_attr_setaffinity_np()");

	rc = pthread_create(&t1, &attr /* Bind to CPU 0 */, tm_una_pong, NULL);
	if (rc)
		pr_err(rc, "pthread_create()");

	/* Name it for systemtap convenience */
	rc = pthread_setname_np(t1, "tm_una_pong");
	if (rc)
		pr_warn(rc, "pthread_create()");

	flags.result = 0;

	for (exception = 0; exception < NUM_EXCEPTIONS; exception++) {
		printf("Checking if FP/VEC registers are sane after");

		if (exception == FP_UNA_EXCEPTION)
			printf(" a FP unavailable exception...\n");

		else if (exception == VEC_UNA_EXCEPTION)
			printf(" a VEC unavailable exception...\n");

		else
			printf(" a VSX unavailable exception...\n");

		flags.exception = exception;

		test_fp_vec(0, 0, &attr);
		test_fp_vec(1, 0, &attr);
		test_fp_vec(0, 1, &attr);
		test_fp_vec(1, 1, &attr);

	}

	if (flags.result > 0) {
		printf("result: failed!\n");
		exit(1);
	} else {
		printf("result: success\n");
		exit(0);
	}
}