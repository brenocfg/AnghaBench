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
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  have_htm () ; 
 int /*<<< orphan*/ * malloc (int) ; 
 scalar_t__ passed ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 scalar_t__ texasr ; 
 scalar_t__ tfiar_tfhar ; 

int test_tmspr()
{
	pthread_t	*thread;
	int	   	thread_num;
	unsigned long	i;

	SKIP_IF(!have_htm());

	/* To cause some context switching */
	thread_num = 10 * sysconf(_SC_NPROCESSORS_ONLN);

	thread = malloc(thread_num * sizeof(pthread_t));
	if (thread == NULL)
		return EXIT_FAILURE;

	/* Test TFIAR and TFHAR */
	for (i = 0; i < thread_num; i += 2) {
		if (pthread_create(&thread[i], NULL, (void *)tfiar_tfhar,
				   (void *)i))
			return EXIT_FAILURE;
	}
	/* Test TEXASR */
	for (i = 1; i < thread_num; i += 2) {
		if (pthread_create(&thread[i], NULL, (void *)texasr, (void *)i))
			return EXIT_FAILURE;
	}

	for (i = 0; i < thread_num; i++) {
		if (pthread_join(thread[i], NULL) != 0)
			return EXIT_FAILURE;
	}

	free(thread);

	if (passed)
		return 0;
	else
		return 1;
}