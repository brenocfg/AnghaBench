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
struct shrink_control {int gfp_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 unsigned long SHRINK_STOP ; 
 int __GFP_FS ; 
 int /*<<< orphan*/  dispose ; 
 int /*<<< orphan*/  gfs2_qd_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_qd_isolate ; 
 int /*<<< orphan*/  gfs2_qd_lru ; 
 unsigned long list_lru_shrink_walk (int /*<<< orphan*/ *,struct shrink_control*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long gfs2_qd_shrink_scan(struct shrinker *shrink,
					 struct shrink_control *sc)
{
	LIST_HEAD(dispose);
	unsigned long freed;

	if (!(sc->gfp_mask & __GFP_FS))
		return SHRINK_STOP;

	freed = list_lru_shrink_walk(&gfs2_qd_lru, sc,
				     gfs2_qd_isolate, &dispose);

	gfs2_qd_dispose(&dispose);

	return freed;
}