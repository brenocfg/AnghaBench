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
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  ida_random_fn ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ida_thread_tests(void)
{
	pthread_t threads[20];
	int i;

	for (i = 0; i < ARRAY_SIZE(threads); i++)
		if (pthread_create(&threads[i], NULL, ida_random_fn, NULL)) {
			perror("creating ida thread");
			exit(1);
		}

	while (i--)
		pthread_join(threads[i], NULL);
}