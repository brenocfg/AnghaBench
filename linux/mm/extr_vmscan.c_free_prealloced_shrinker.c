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
struct shrinker {int flags; int /*<<< orphan*/ * nr_deferred; } ;

/* Variables and functions */
 int SHRINKER_MEMCG_AWARE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_memcg_shrinker (struct shrinker*) ; 

void free_prealloced_shrinker(struct shrinker *shrinker)
{
	if (!shrinker->nr_deferred)
		return;

	if (shrinker->flags & SHRINKER_MEMCG_AWARE)
		unregister_memcg_shrinker(shrinker);

	kfree(shrinker->nr_deferred);
	shrinker->nr_deferred = NULL;
}