#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ rd_isnailed; scalar_t__ rd_isvalid; TYPE_1__* rd_rel; } ;
struct TYPE_10__ {scalar_t__ relkind; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int IsTransactionState () ; 
 scalar_t__ RELKIND_INDEX ; 
 scalar_t__ RELKIND_PARTITIONED_INDEX ; 
 TYPE_2__* RelationBuildDesc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RelationClearRelation (TYPE_2__*,int) ; 
 int /*<<< orphan*/  RelationIdCacheLookup (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  RelationIncrementReferenceCount (TYPE_2__*) ; 
 scalar_t__ RelationIsValid (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationReloadIndexInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  criticalRelcachesBuilt ; 

Relation
RelationIdGetRelation(Oid relationId)
{
	Relation	rd;

	/* Make sure we're in an xact, even if this ends up being a cache hit */
	Assert(IsTransactionState());

	/*
	 * first try to find reldesc in the cache
	 */
	RelationIdCacheLookup(relationId, rd);

	if (RelationIsValid(rd))
	{
		RelationIncrementReferenceCount(rd);
		/* revalidate cache entry if necessary */
		if (!rd->rd_isvalid)
		{
			/*
			 * Indexes only have a limited number of possible schema changes,
			 * and we don't want to use the full-blown procedure because it's
			 * a headache for indexes that reload itself depends on.
			 */
			if (rd->rd_rel->relkind == RELKIND_INDEX ||
				rd->rd_rel->relkind == RELKIND_PARTITIONED_INDEX)
				RelationReloadIndexInfo(rd);
			else
				RelationClearRelation(rd, true);

			/*
			 * Normally entries need to be valid here, but before the relcache
			 * has been initialized, not enough infrastructure exists to
			 * perform pg_class lookups. The structure of such entries doesn't
			 * change, but we still want to update the rd_rel entry. So
			 * rd_isvalid = false is left in place for a later lookup.
			 */
			Assert(rd->rd_isvalid ||
				   (rd->rd_isnailed && !criticalRelcachesBuilt));
		}
		return rd;
	}

	/*
	 * no reldesc in the cache, so have RelationBuildDesc() build one and add
	 * it.
	 */
	rd = RelationBuildDesc(relationId, true);
	if (RelationIsValid(rd))
		RelationIncrementReferenceCount(rd);
	return rd;
}