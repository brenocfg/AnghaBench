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
struct pool {struct pool* next; struct pool* mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct pool*) ; 
 struct pool* pool_head ; 

void names_free(void)
{
	struct pool *pool;

	if (!pool_head)
		return;

	for (pool = pool_head; pool != NULL; ) {
		struct pool *tmp;

		if (pool->mem)
			free(pool->mem);

		tmp = pool;
		pool = pool->next;
		free(tmp);
	}
}