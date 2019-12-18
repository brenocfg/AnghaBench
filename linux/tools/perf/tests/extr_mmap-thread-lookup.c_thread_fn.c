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
struct thread_data {int /*<<< orphan*/  map; int /*<<< orphan*/ * ready; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  go_away ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_size ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ thread_init (struct thread_data*) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int write (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void *thread_fn(void *arg)
{
	struct thread_data *td = arg;
	ssize_t ret;
	int go = 0;

	if (thread_init(td))
		return NULL;

	/* Signal thread_create thread is initialized. */
	ret = write(td->ready[1], &go, sizeof(int));
	if (ret != sizeof(int)) {
		pr_err("failed to notify\n");
		return NULL;
	}

	while (!go_away) {
		/* Waiting for main thread to kill us. */
		usleep(100);
	}

	munmap(td->map, page_size);
	return NULL;
}