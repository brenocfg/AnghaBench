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
struct child_sync {int /*<<< orphan*/  sem_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  perror (char*) ; 
 int sem_post (int /*<<< orphan*/ *) ; 

int prod_parent(struct child_sync *sync)
{
	int ret;

	/* Unblock the parent now. */
	ret = sem_post(&sync->sem_parent);
	if (ret) {
		perror("Error prodding parent");
		return 1;
	}

	return 0;
}