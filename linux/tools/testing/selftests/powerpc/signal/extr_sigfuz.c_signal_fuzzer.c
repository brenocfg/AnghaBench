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
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int nthread ; 
 int /*<<< orphan*/  perror (char*) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigfuz_test ; 

__attribute__((used)) static int signal_fuzzer(void)
{
	int t, rc;
	pthread_t *threads;

	threads = malloc(nthread * sizeof(pthread_t));

	for (t = 0; t < nthread; t++) {
		rc = pthread_create(&threads[t], NULL, sigfuz_test,
				    (void *)&t);
		if (rc)
			perror("Thread creation error\n");
	}

	for (t = 0; t < nthread; t++) {
		rc = pthread_join(threads[t], NULL);
		if (rc)
			perror("Thread join error\n");
	}

	free(threads);

	return EXIT_SUCCESS;
}