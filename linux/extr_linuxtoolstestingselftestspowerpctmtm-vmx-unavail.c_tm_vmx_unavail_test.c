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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  have_htm () ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int passed ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  worker ; 

int tm_vmx_unavail_test()
{
	int threads;
	pthread_t *thread;

	SKIP_IF(!have_htm());

	passed = 1;

	threads = sysconf(_SC_NPROCESSORS_ONLN) * 4;
	thread = malloc(sizeof(pthread_t)*threads);
	if (!thread)
		return EXIT_FAILURE;

	for (uint64_t i = 0; i < threads; i++)
		pthread_create(&thread[i], NULL, &worker, NULL);

	for (uint64_t i = 0; i < threads; i++)
		pthread_join(thread[i], NULL);

	free(thread);

	return passed ? EXIT_SUCCESS : EXIT_FAILURE;
}