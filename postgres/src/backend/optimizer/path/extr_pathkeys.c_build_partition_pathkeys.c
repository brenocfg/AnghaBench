#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int partnatts; int /*<<< orphan*/ * partcollation; int /*<<< orphan*/ * partopcintype; int /*<<< orphan*/ * partopfamily; } ;
struct TYPE_6__ {int /*<<< orphan*/  relids; int /*<<< orphan*/ * partexprs; int /*<<< orphan*/  nparts; int /*<<< orphan*/  boundinfo; TYPE_2__* part_scheme; } ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  TYPE_1__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  PathKey ;
typedef  TYPE_2__* PartitionScheme ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_SIMPLE_REL (TYPE_1__*) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  ScanDirectionIsBackward (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ linitial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * make_pathkey_from_sortinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  partitions_are_ordered (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  partkey_is_bool_constant_for_query (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pathkey_is_redundant (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

List *
build_partition_pathkeys(PlannerInfo *root, RelOptInfo *partrel,
						 ScanDirection scandir, bool *partialkeys)
{
	List	   *retval = NIL;
	PartitionScheme partscheme = partrel->part_scheme;
	int			i;

	Assert(partscheme != NULL);
	Assert(partitions_are_ordered(partrel->boundinfo, partrel->nparts));
	/* For now, we can only cope with baserels */
	Assert(IS_SIMPLE_REL(partrel));

	for (i = 0; i < partscheme->partnatts; i++)
	{
		PathKey    *cpathkey;
		Expr	   *keyCol = (Expr *) linitial(partrel->partexprs[i]);

		/*
		 * Try to make a canonical pathkey for this partkey.
		 *
		 * We're considering a baserel scan, so nullable_relids should be
		 * NULL.  Also, we assume the PartitionDesc lists any NULL partition
		 * last, so we treat the scan like a NULLS LAST index: we have
		 * nulls_first for backwards scan only.
		 */
		cpathkey = make_pathkey_from_sortinfo(root,
											  keyCol,
											  NULL,
											  partscheme->partopfamily[i],
											  partscheme->partopcintype[i],
											  partscheme->partcollation[i],
											  ScanDirectionIsBackward(scandir),
											  ScanDirectionIsBackward(scandir),
											  0,
											  partrel->relids,
											  false);


		if (cpathkey)
		{
			/*
			 * We found the sort key in an EquivalenceClass, so it's relevant
			 * for this query.  Add it to list, unless it's redundant.
			 */
			if (!pathkey_is_redundant(cpathkey, retval))
				retval = lappend(retval, cpathkey);
		}
		else
		{
			/*
			 * Boolean partition keys might be redundant even if they do not
			 * appear in an EquivalenceClass, because of our special treatment
			 * of boolean equality conditions --- see the comment for
			 * partkey_is_bool_constant_for_query().  If that applies, we can
			 * continue to examine lower-order partition keys.  Otherwise, the
			 * sort key is not an interesting sort order for this query, so we
			 * should stop considering partition columns; any lower-order sort
			 * keys won't be useful either.
			 */
			if (!partkey_is_bool_constant_for_query(partrel, i))
			{
				*partialkeys = true;
				return retval;
			}
		}
	}

	*partialkeys = false;
	return retval;
}