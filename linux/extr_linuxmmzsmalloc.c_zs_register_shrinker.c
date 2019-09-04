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
struct TYPE_2__ {int /*<<< orphan*/  seeks; scalar_t__ batch; int /*<<< orphan*/  count_objects; int /*<<< orphan*/  scan_objects; } ;
struct zs_pool {TYPE_1__ shrinker; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SEEKS ; 
 int register_shrinker (TYPE_1__*) ; 
 int /*<<< orphan*/  zs_shrinker_count ; 
 int /*<<< orphan*/  zs_shrinker_scan ; 

__attribute__((used)) static int zs_register_shrinker(struct zs_pool *pool)
{
	pool->shrinker.scan_objects = zs_shrinker_scan;
	pool->shrinker.count_objects = zs_shrinker_count;
	pool->shrinker.batch = 0;
	pool->shrinker.seeks = DEFAULT_SEEKS;

	return register_shrinker(&pool->shrinker);
}