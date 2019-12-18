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
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int ITERATIONS ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int THREAD_FACTOR ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 scalar_t__ bad_context ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  pthread_kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int running ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_vmx_c ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 int threads_starting ; 
 int /*<<< orphan*/  usleep (int) ; 

int test_signal_vmx(void)
{
	int i, j, rc, threads;
	void *rc_p;
	pthread_t *tids;

	threads = sysconf(_SC_NPROCESSORS_ONLN) * THREAD_FACTOR;
	tids = malloc(threads * sizeof(pthread_t));
	FAIL_IF(!tids);

	running = true;
	threads_starting = threads;
	for (i = 0; i < threads; i++) {
		rc = pthread_create(&tids[i], NULL, signal_vmx_c, NULL);
		FAIL_IF(rc);
	}

	setbuf(stdout, NULL);
	printf("\tWaiting for %d workers to start... %d", threads, threads_starting);
	while (threads_starting) {
		asm volatile("": : :"memory");
		usleep(1000);
		printf(", %d", threads_starting);
	}
	printf(" ...done\n");

	printf("\tSending signals to all threads %d times...", ITERATIONS);
	for (i = 0; i < ITERATIONS; i++) {
		for (j = 0; j < threads; j++) {
			pthread_kill(tids[j], SIGUSR1);
		}
		sleep(1);
	}
	printf("done\n");

	printf("\tKilling workers...");
	running = 0;
	for (i = 0; i < threads; i++) {
		pthread_join(tids[i], &rc_p);

		/*
		 * Harness will say the fail was here, look at why signal_vmx
		 * returned
		 */
		if ((long) rc_p || bad_context)
			printf("oops\n");
		if (bad_context)
			fprintf(stderr, "\t!! bad_context is true\n");
		FAIL_IF((long) rc_p || bad_context);
	}
	printf("done\n");

	free(tids);
	return 0;
}