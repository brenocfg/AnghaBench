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
typedef  int /*<<< orphan*/  PlaceHolderVar ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phid ; 
 int /*<<< orphan*/  phlevelsup ; 

__attribute__((used)) static bool
_equalPlaceHolderVar(const PlaceHolderVar *a, const PlaceHolderVar *b)
{
	/*
	 * We intentionally do not compare phexpr.  Two PlaceHolderVars with the
	 * same ID and levelsup should be considered equal even if the contained
	 * expressions have managed to mutate to different states.  This will
	 * happen during final plan construction when there are nested PHVs, since
	 * the inner PHV will get replaced by a Param in some copies of the outer
	 * PHV.  Another way in which it can happen is that initplan sublinks
	 * could get replaced by differently-numbered Params when sublink folding
	 * is done.  (The end result of such a situation would be some
	 * unreferenced initplans, which is annoying but not really a problem.) On
	 * the same reasoning, there is no need to examine phrels.
	 *
	 * COMPARE_NODE_FIELD(phexpr);
	 *
	 * COMPARE_BITMAPSET_FIELD(phrels);
	 */
	COMPARE_SCALAR_FIELD(phid);
	COMPARE_SCALAR_FIELD(phlevelsup);

	return true;
}