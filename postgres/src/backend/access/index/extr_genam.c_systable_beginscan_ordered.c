#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_2__* rd_index; } ;
struct TYPE_20__ {int sk_attno; } ;
struct TYPE_19__ {int /*<<< orphan*/ * scan; int /*<<< orphan*/  iscan; int /*<<< orphan*/ * snapshot; int /*<<< orphan*/  slot; TYPE_5__* irel; TYPE_5__* heap_rel; } ;
struct TYPE_17__ {int* values; } ;
struct TYPE_18__ {TYPE_1__ indkey; } ;
typedef  int /*<<< orphan*/  SysScanDescData ;
typedef  TYPE_3__* SysScanDesc ;
typedef  int /*<<< orphan*/ * Snapshot ;
typedef  TYPE_4__* ScanKey ;
typedef  TYPE_5__* Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetCatalogSnapshot (int /*<<< orphan*/ ) ; 
 scalar_t__ IgnoreSystemIndexes ; 
 int IndexRelationGetNumberOfAttributes (TYPE_5__*) ; 
 int /*<<< orphan*/ * RegisterSnapshot (int /*<<< orphan*/ ) ; 
 scalar_t__ ReindexIsProcessingIndex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_5__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_5__*) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  index_beginscan (TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_rescan (int /*<<< orphan*/ ,TYPE_4__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  table_slot_create (TYPE_5__*,int /*<<< orphan*/ *) ; 

SysScanDesc
systable_beginscan_ordered(Relation heapRelation,
						   Relation indexRelation,
						   Snapshot snapshot,
						   int nkeys, ScanKey key)
{
	SysScanDesc sysscan;
	int			i;

	/* REINDEX can probably be a hard error here ... */
	if (ReindexIsProcessingIndex(RelationGetRelid(indexRelation)))
		elog(ERROR, "cannot do ordered scan on index \"%s\", because it is being reindexed",
			 RelationGetRelationName(indexRelation));
	/* ... but we only throw a warning about violating IgnoreSystemIndexes */
	if (IgnoreSystemIndexes)
		elog(WARNING, "using index \"%s\" despite IgnoreSystemIndexes",
			 RelationGetRelationName(indexRelation));

	sysscan = (SysScanDesc) palloc(sizeof(SysScanDescData));

	sysscan->heap_rel = heapRelation;
	sysscan->irel = indexRelation;
	sysscan->slot = table_slot_create(heapRelation, NULL);

	if (snapshot == NULL)
	{
		Oid			relid = RelationGetRelid(heapRelation);

		snapshot = RegisterSnapshot(GetCatalogSnapshot(relid));
		sysscan->snapshot = snapshot;
	}
	else
	{
		/* Caller is responsible for any snapshot. */
		sysscan->snapshot = NULL;
	}

	/* Change attribute numbers to be index column numbers. */
	for (i = 0; i < nkeys; i++)
	{
		int			j;

		for (j = 0; j < IndexRelationGetNumberOfAttributes(indexRelation); j++)
		{
			if (key[i].sk_attno == indexRelation->rd_index->indkey.values[j])
			{
				key[i].sk_attno = j + 1;
				break;
			}
		}
		if (j == IndexRelationGetNumberOfAttributes(indexRelation))
			elog(ERROR, "column is not in index");
	}

	sysscan->iscan = index_beginscan(heapRelation, indexRelation,
									 snapshot, nkeys, 0);
	index_rescan(sysscan->iscan, key, nkeys, NULL, 0);
	sysscan->scan = NULL;

	return sysscan;
}