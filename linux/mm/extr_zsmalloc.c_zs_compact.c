#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long pages_compacted; } ;
struct zs_pool {TYPE_1__ stats; struct size_class** size_class; } ;
struct size_class {int index; } ;

/* Variables and functions */
 int ZS_SIZE_CLASSES ; 
 int /*<<< orphan*/  __zs_compact (struct zs_pool*,struct size_class*) ; 

unsigned long zs_compact(struct zs_pool *pool)
{
	int i;
	struct size_class *class;

	for (i = ZS_SIZE_CLASSES - 1; i >= 0; i--) {
		class = pool->size_class[i];
		if (!class)
			continue;
		if (class->index != i)
			continue;
		__zs_compact(pool, class);
	}

	return pool->stats.pages_compacted;
}