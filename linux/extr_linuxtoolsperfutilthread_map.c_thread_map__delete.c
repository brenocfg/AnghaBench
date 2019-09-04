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
struct thread_map {int nr; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  free (struct thread_map*) ; 
 scalar_t__ refcount_read (int /*<<< orphan*/ *) ; 
 struct thread_map* thread_map__comm (struct thread_map*,int) ; 

__attribute__((used)) static void thread_map__delete(struct thread_map *threads)
{
	if (threads) {
		int i;

		WARN_ONCE(refcount_read(&threads->refcnt) != 0,
			  "thread map refcnt unbalanced\n");
		for (i = 0; i < threads->nr; i++)
			free(thread_map__comm(threads, i));
		free(threads);
	}
}