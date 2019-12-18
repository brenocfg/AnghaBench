#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_2__* rd_index; } ;
struct TYPE_21__ {int sk_attno; } ;
struct TYPE_20__ {int /*<<< orphan*/ * iscan; int /*<<< orphan*/ * scan; int /*<<< orphan*/ * snapshot; int /*<<< orphan*/  slot; TYPE_5__* irel; TYPE_5__* heap_rel; } ;
struct TYPE_18__ {int* values; } ;
struct TYPE_19__ {TYPE_1__ indkey; } ;
typedef  int /*<<< orphan*/  SysScanDescData ;
typedef  TYPE_3__* SysScanDesc ;
typedef  int /*<<< orphan*/ * Snapshot ;
typedef  TYPE_4__* ScanKey ;
typedef  TYPE_5__* Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetCatalogSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IgnoreSystemIndexes ; 
 int IndexRelationGetNumberOfAttributes (TYPE_5__*) ; 
 int /*<<< orphan*/ * RegisterSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReindexIsProcessingIndex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_5__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * index_beginscan (TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_5__* index_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_rescan (int /*<<< orphan*/ *,TYPE_4__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/ * table_beginscan_strat (TYPE_5__*,int /*<<< orphan*/ *,int,TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  table_slot_create (TYPE_5__*,int /*<<< orphan*/ *) ; 

SysScanDesc
systable_beginscan(Relation heapRelation,
				   Oid indexId,
				   bool indexOK,
				   Snapshot snapshot,
				   int nkeys, ScanKey key)
{
	SysScanDesc sysscan;
	Relation	irel;

	if (indexOK &&
		!IgnoreSystemIndexes &&
		!ReindexIsProcessingIndex(indexId))
		irel = index_open(indexId, AccessShareLock);
	else
		irel = NULL;

	sysscan = (SysScanDesc) palloc(sizeof(SysScanDescData));

	sysscan->heap_rel = heapRelation;
	sysscan->irel = irel;
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

	if (irel)
	{
		int			i;

		/* Change attribute numbers to be index column numbers. */
		for (i = 0; i < nkeys; i++)
		{
			int			j;

			for (j = 0; j < IndexRelationGetNumberOfAttributes(irel); j++)
			{
				if (key[i].sk_attno == irel->rd_index->indkey.values[j])
				{
					key[i].sk_attno = j + 1;
					break;
				}
			}
			if (j == IndexRelationGetNumberOfAttributes(irel))
				elog(ERROR, "column is not in index");
		}

		sysscan->iscan = index_beginscan(heapRelation, irel,
										 snapshot, nkeys, 0);
		index_rescan(sysscan->iscan, key, nkeys, NULL, 0);
		sysscan->scan = NULL;
	}
	else
	{
		/*
		 * We disallow synchronized scans when forced to use a heapscan on a
		 * catalog.  In most cases the desired rows are near the front, so
		 * that the unpredictable start point of a syncscan is a serious
		 * disadvantage; and there are no compensating advantages, because
		 * it's unlikely that such scans will occur in parallel.
		 */
		sysscan->scan = table_beginscan_strat(heapRelation, snapshot,
											  nkeys, key,
											  true, false);
		sysscan->iscan = NULL;
	}

	return sysscan;
}