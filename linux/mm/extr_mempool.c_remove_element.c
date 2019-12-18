#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t curr_nr; void** elements; } ;
typedef  TYPE_1__ mempool_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  check_element (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  kasan_unpoison_element (TYPE_1__*,void*) ; 

__attribute__((used)) static void *remove_element(mempool_t *pool)
{
	void *element = pool->elements[--pool->curr_nr];

	BUG_ON(pool->curr_nr < 0);
	kasan_unpoison_element(pool, element);
	check_element(pool, element);
	return element;
}