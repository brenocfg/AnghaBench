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
struct thread {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int idle_max_cpu ; 
 int /*<<< orphan*/ ** idle_threads ; 
 int init_idle_thread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * thread__new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** zalloc (int) ; 

__attribute__((used)) static int init_idle_threads(int ncpu)
{
	int i, ret;

	idle_threads = zalloc(ncpu * sizeof(struct thread *));
	if (!idle_threads)
		return -ENOMEM;

	idle_max_cpu = ncpu;

	/* allocate the actual thread struct if needed */
	for (i = 0; i < ncpu; ++i) {
		idle_threads[i] = thread__new(0, 0);
		if (idle_threads[i] == NULL)
			return -ENOMEM;

		ret = init_idle_thread(idle_threads[i]);
		if (ret < 0)
			return ret;
	}

	return 0;
}