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
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ profiler_name_store_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 TYPE_1__* bzalloc (int) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

profiler_name_store_t *profiler_name_store_create(void)
{
	profiler_name_store_t *store = bzalloc(sizeof(profiler_name_store_t));

	if (pthread_mutex_init(&store->mutex, NULL))
		goto error;

	return store;

error:
	bfree(store);
	return NULL;
}