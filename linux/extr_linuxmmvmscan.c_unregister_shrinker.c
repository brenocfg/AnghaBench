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
struct shrinker {int flags; int /*<<< orphan*/ * nr_deferred; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int SHRINKER_MEMCG_AWARE ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shrinker_rwsem ; 
 int /*<<< orphan*/  unregister_memcg_shrinker (struct shrinker*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void unregister_shrinker(struct shrinker *shrinker)
{
	if (!shrinker->nr_deferred)
		return;
	if (shrinker->flags & SHRINKER_MEMCG_AWARE)
		unregister_memcg_shrinker(shrinker);
	down_write(&shrinker_rwsem);
	list_del(&shrinker->list);
	up_write(&shrinker_rwsem);
	kfree(shrinker->nr_deferred);
	shrinker->nr_deferred = NULL;
}