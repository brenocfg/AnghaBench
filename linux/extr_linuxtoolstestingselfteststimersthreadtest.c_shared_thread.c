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

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ LISTSIZE ; 
 int /*<<< orphan*/  checklist (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/ * global_list ; 
 int /*<<< orphan*/  list_lock ; 
 scalar_t__ listcount ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void *shared_thread(void *arg)
{
	while (!done) {
		/* protect the list */
		pthread_mutex_lock(&list_lock);

		/* see if we're ready to check the list */
		if (listcount >= LISTSIZE) {
			checklist(global_list, LISTSIZE);
			listcount = 0;
		}
		clock_gettime(CLOCK_MONOTONIC, &global_list[listcount++]);

		pthread_mutex_unlock(&list_lock);
	}
	return NULL;
}