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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printv (int,char*) ; 
 int /*<<< orphan*/  pthread_barrier_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regression1_fn ; 
 int /*<<< orphan*/ * threads ; 
 int /*<<< orphan*/  worker_barrier ; 

void regression1_test(void)
{
	int nr_threads;
	int i;
	long arg;

	/* Regression #1 */
	printv(1, "running regression test 1, should finish in under a minute\n");
	nr_threads = 2;
	pthread_barrier_init(&worker_barrier, NULL, nr_threads);

	threads = malloc(nr_threads * sizeof(pthread_t *));

	for (i = 0; i < nr_threads; i++) {
		arg = i;
		if (pthread_create(&threads[i], NULL, regression1_fn, (void *)arg)) {
			perror("pthread_create");
			exit(1);
		}
	}

	for (i = 0; i < nr_threads; i++) {
		if (pthread_join(threads[i], NULL)) {
			perror("pthread_join");
			exit(1);
		}
	}

	free(threads);

	printv(1, "regression test 1, done\n");
}