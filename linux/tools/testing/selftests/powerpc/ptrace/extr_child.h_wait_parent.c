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
struct child_sync {int parent_gave_up; int /*<<< orphan*/  sem_child; } ;

/* Variables and functions */
 int /*<<< orphan*/  perror (char*) ; 
 int sem_wait (int /*<<< orphan*/ *) ; 

int wait_parent(struct child_sync *sync)
{
	int ret;

	/* Wait until the parent prods us. */
	ret = sem_wait(&sync->sem_child);
	if (ret) {
		perror("Error waiting for parent");
		return 1;
	}

	return sync->parent_gave_up;
}