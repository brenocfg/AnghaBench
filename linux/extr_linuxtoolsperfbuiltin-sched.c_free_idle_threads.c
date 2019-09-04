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
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int idle_max_cpu ; 
 scalar_t__* idle_threads ; 
 int /*<<< orphan*/  thread__delete (scalar_t__) ; 

__attribute__((used)) static void free_idle_threads(void)
{
	int i;

	if (idle_threads == NULL)
		return;

	for (i = 0; i < idle_max_cpu; ++i) {
		if ((idle_threads[i]))
			thread__delete(idle_threads[i]);
	}

	free(idle_threads);
}