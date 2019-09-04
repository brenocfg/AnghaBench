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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (long) ; 
 int PREEMPT_TIME ; 
 int THREAD_FACTOR ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  preempt_vsx_c ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 
 int running ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stdout ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 int threads_starting ; 

int test_preempt_vsx(void)
{
	int i, rc, threads;
	pthread_t *tids;

	threads = sysconf(_SC_NPROCESSORS_ONLN) * THREAD_FACTOR;
	tids = malloc(threads * sizeof(pthread_t));
	FAIL_IF(!tids);

	running = true;
	threads_starting = threads;
	for (i = 0; i < threads; i++) {
		rc = pthread_create(&tids[i], NULL, preempt_vsx_c, NULL);
		FAIL_IF(rc);
	}

	setbuf(stdout, NULL);
	/* Not really nessesary but nice to wait for every thread to start */
	printf("\tWaiting for %d workers to start...", threads_starting);
	while(threads_starting)
		asm volatile("": : :"memory");
	printf("done\n");

	printf("\tWaiting for %d seconds to let some workers get preempted...", PREEMPT_TIME);
	sleep(PREEMPT_TIME);
	printf("done\n");

	printf("\tStopping workers...");
	/*
	 * Working are checking this value every loop. In preempt_vsx 'cmpwi r5,0; bne 2b'.
	 * r5 will have loaded the value of running.
	 */
	running = 0;
	for (i = 0; i < threads; i++) {
		void *rc_p;
		pthread_join(tids[i], &rc_p);

		/*
		 * Harness will say the fail was here, look at why preempt_vsx
		 * returned
		 */
		if ((long) rc_p)
			printf("oops\n");
		FAIL_IF((long) rc_p);
	}
	printf("done\n");

	return 0;
}