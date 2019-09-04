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
struct shrinker {int dummy; } ;
struct shrink_control {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * counter; } ;

/* Variables and functions */
 size_t DQST_FREE_DQUOTS ; 
 TYPE_1__ dqstats ; 
 int /*<<< orphan*/  percpu_counter_read_positive (int /*<<< orphan*/ *) ; 
 unsigned long vfs_pressure_ratio (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long
dqcache_shrink_count(struct shrinker *shrink, struct shrink_control *sc)
{
	return vfs_pressure_ratio(
	percpu_counter_read_positive(&dqstats.counter[DQST_FREE_DQUOTS]));
}