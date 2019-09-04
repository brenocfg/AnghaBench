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
struct child_sync {int /*<<< orphan*/  sem_child; int /*<<< orphan*/  sem_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  perror (char*) ; 
 int sem_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int init_child_sync(struct child_sync *sync)
{
	int ret;

	ret = sem_init(&sync->sem_parent, 1, 0);
	if (ret) {
		perror("Semaphore initialization failed");
		return 1;
	}

	ret = sem_init(&sync->sem_child, 1, 0);
	if (ret) {
		perror("Semaphore initialization failed");
		return 1;
	}

	return 0;
}