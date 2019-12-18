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
struct thread_arg {scalar_t__ ret; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUTEX_PRIVATE_FLAG ; 
 scalar_t__ RET_ERROR ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2 ; 
 scalar_t__ futex_lock_pi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int futex_unlock_pi (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ futex_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_exit (void*) ; 
 int /*<<< orphan*/  wake_complete ; 

void *third_party_blocker(void *arg)
{
	struct thread_arg *args = (struct thread_arg *)arg;
	int ret2 = 0;

	args->ret = futex_lock_pi(&f2, NULL, 0, FUTEX_PRIVATE_FLAG);
	if (args->ret)
		goto out;
	args->ret = futex_wait(&wake_complete, wake_complete, NULL,
			       FUTEX_PRIVATE_FLAG);
	ret2 = futex_unlock_pi(&f2, FUTEX_PRIVATE_FLAG);

 out:
	if (args->ret || ret2) {
		error("third_party_blocker() futex error", 0);
		args->ret = RET_ERROR;
	}

	pthread_exit((void *)&args->ret);
}