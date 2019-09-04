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
struct TYPE_2__ {int touch_fp; int touch_vec; int result; } ;

/* Variables and functions */
 scalar_t__ DEBUG ; 
 TYPE_1__ flags ; 
 int /*<<< orphan*/  pr_err (int,char*) ; 
 int /*<<< orphan*/  pr_warn (int,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int pthread_join (int /*<<< orphan*/ ,void**) ; 
 int pthread_setname_np (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tm_una_ping ; 

void test_fp_vec(int fp, int vec, pthread_attr_t *attr)
{
	int retries = 2;
	void *ret_value;
	pthread_t t0;

	flags.touch_fp = fp;
	flags.touch_vec = vec;

	/*
	 * Without luck it's possible that the transaction is aborted not due to
	 * the unavailable exception caught in the middle as we expect but also,
	 * for instance, due to a context switch or due to a KVM reschedule (if
	 * it's running on a VM). Thus we try a few times before giving up,
	 * checking if the failure cause is the one we expect.
	 */
	do {
		int rc;

		/* Bind to CPU 0, as specified in 'attr'. */
		rc = pthread_create(&t0, attr, tm_una_ping, (void *) &flags);
		if (rc)
			pr_err(rc, "pthread_create()");
		rc = pthread_setname_np(t0, "tm_una_ping");
		if (rc)
			pr_warn(rc, "pthread_setname_np");
		rc = pthread_join(t0, &ret_value);
		if (rc)
			pr_err(rc, "pthread_join");

		retries--;
	} while (ret_value != NULL && retries);

	if (!retries) {
		flags.result = 1;
		if (DEBUG)
			printf("All transactions failed unexpectedly\n");

	}
}