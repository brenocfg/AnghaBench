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
struct shrinker {int dummy; } ;
struct shrink_control {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gfs2_qd_lru ; 
 int /*<<< orphan*/  list_lru_shrink_count (int /*<<< orphan*/ *,struct shrink_control*) ; 
 unsigned long vfs_pressure_ratio (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long gfs2_qd_shrink_count(struct shrinker *shrink,
					  struct shrink_control *sc)
{
	return vfs_pressure_ratio(list_lru_shrink_count(&gfs2_qd_lru, sc));
}