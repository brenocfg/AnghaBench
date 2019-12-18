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
typedef  int /*<<< orphan*/ * Relids ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * bms_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bms_del_members (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bms_free (int /*<<< orphan*/ *) ; 
 scalar_t__ bms_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bms_overlap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bms_union (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

Relids
calc_nestloop_required_outer(Relids outerrelids,
							 Relids outer_paramrels,
							 Relids innerrelids,
							 Relids inner_paramrels)
{
	Relids		required_outer;

	/* inner_path can require rels from outer path, but not vice versa */
	Assert(!bms_overlap(outer_paramrels, innerrelids));
	/* easy case if inner path is not parameterized */
	if (!inner_paramrels)
		return bms_copy(outer_paramrels);
	/* else, form the union ... */
	required_outer = bms_union(outer_paramrels, inner_paramrels);
	/* ... and remove any mention of now-satisfied outer rels */
	required_outer = bms_del_members(required_outer,
									 outerrelids);
	/* maintain invariant that required_outer is exactly NULL if empty */
	if (bms_is_empty(required_outer))
	{
		bms_free(required_outer);
		required_outer = NULL;
	}
	return required_outer;
}