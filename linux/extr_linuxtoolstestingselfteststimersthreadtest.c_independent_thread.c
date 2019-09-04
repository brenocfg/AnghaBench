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
struct timespec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int LISTSIZE ; 
 int /*<<< orphan*/  checklist (struct timespec*,int) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  done ; 

void *independent_thread(void *arg)
{
	struct timespec my_list[LISTSIZE];
	int count;

	while (!done) {
		/* fill the list */
		for (count = 0; count < LISTSIZE; count++)
			clock_gettime(CLOCK_MONOTONIC, &my_list[count]);
		checklist(my_list, LISTSIZE);
	}
	return NULL;
}