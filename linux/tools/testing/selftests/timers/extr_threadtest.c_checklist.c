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
struct timespec {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;

/* Variables and functions */
 int done ; 
 int /*<<< orphan*/  print_lock ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void checklist(struct timespec *list, int size)
{
	int i, j;
	struct timespec *a, *b;

	/* scan the list */
	for (i = 0; i < size-1; i++) {
		a = &list[i];
		b = &list[i+1];

		/* look for any time inconsistencies */
		if ((b->tv_sec <= a->tv_sec) &&
			(b->tv_nsec < a->tv_nsec)) {

			/* flag other threads */
			done = 1;

			/*serialize printing to avoid junky output*/
			pthread_mutex_lock(&print_lock);

			/* dump the list */
			printf("\n");
			for (j = 0; j < size; j++) {
				if (j == i)
					printf("---------------\n");
				printf("%lu:%lu\n", list[j].tv_sec, list[j].tv_nsec);
				if (j == i+1)
					printf("---------------\n");
			}
			printf("[FAILED]\n");

			pthread_mutex_unlock(&print_lock);
		}
	}
}