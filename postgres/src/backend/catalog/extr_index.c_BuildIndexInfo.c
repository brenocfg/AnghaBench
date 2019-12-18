#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ * values; } ;
struct TYPE_17__ {int indnatts; scalar_t__ indisexclusion; TYPE_2__ indkey; int /*<<< orphan*/  indisready; int /*<<< orphan*/  indisunique; int /*<<< orphan*/  indnkeyatts; } ;
struct TYPE_16__ {int /*<<< orphan*/  ii_ExclusionStrats; int /*<<< orphan*/  ii_ExclusionProcs; int /*<<< orphan*/  ii_ExclusionOps; int /*<<< orphan*/ * ii_IndexAttrNumbers; } ;
struct TYPE_15__ {TYPE_1__* rd_rel; TYPE_5__* rd_index; } ;
struct TYPE_13__ {int /*<<< orphan*/  relam; } ;
typedef  TYPE_3__* Relation ;
typedef  TYPE_4__ IndexInfo ;
typedef  TYPE_5__* Form_pg_index ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int INDEX_MAX_KEYS ; 
 int /*<<< orphan*/  RelationGetExclusionInfo (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RelationGetIndexExpressions (TYPE_3__*) ; 
 int /*<<< orphan*/  RelationGetIndexPredicate (TYPE_3__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_3__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* makeIndexInfo (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

IndexInfo *
BuildIndexInfo(Relation index)
{
	IndexInfo  *ii;
	Form_pg_index indexStruct = index->rd_index;
	int			i;
	int			numAtts;

	/* check the number of keys, and copy attr numbers into the IndexInfo */
	numAtts = indexStruct->indnatts;
	if (numAtts < 1 || numAtts > INDEX_MAX_KEYS)
		elog(ERROR, "invalid indnatts %d for index %u",
			 numAtts, RelationGetRelid(index));

	/*
	 * Create the node, fetching any expressions needed for expressional
	 * indexes and index predicate if any.
	 */
	ii = makeIndexInfo(indexStruct->indnatts,
					   indexStruct->indnkeyatts,
					   index->rd_rel->relam,
					   RelationGetIndexExpressions(index),
					   RelationGetIndexPredicate(index),
					   indexStruct->indisunique,
					   indexStruct->indisready,
					   false);

	/* fill in attribute numbers */
	for (i = 0; i < numAtts; i++)
		ii->ii_IndexAttrNumbers[i] = indexStruct->indkey.values[i];

	/* fetch exclusion constraint info if any */
	if (indexStruct->indisexclusion)
	{
		RelationGetExclusionInfo(index,
								 &ii->ii_ExclusionOps,
								 &ii->ii_ExclusionProcs,
								 &ii->ii_ExclusionStrats);
	}

	return ii;
}