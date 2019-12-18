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
 int /*<<< orphan*/  sem_destroy (int /*<<< orphan*/ *) ; 

void destroy_child_sync(struct child_sync *sync)
{
	sem_destroy(&sync->sem_parent);
	sem_destroy(&sync->sem_child);
}