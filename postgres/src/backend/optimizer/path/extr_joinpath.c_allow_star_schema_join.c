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
typedef  int /*<<< orphan*/  Relids ;
typedef  int /*<<< orphan*/  PlannerInfo ;

/* Variables and functions */
 scalar_t__ bms_nonempty_difference (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bms_overlap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
allow_star_schema_join(PlannerInfo *root,
					   Relids outerrelids,
					   Relids inner_paramrels)
{
	/*
	 * It's a star-schema case if the outer rel provides some but not all of
	 * the inner rel's parameterization.
	 */
	return (bms_overlap(inner_paramrels, outerrelids) &&
			bms_nonempty_difference(inner_paramrels, outerrelids));
}