#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ctl ;
struct TYPE_14__ {int keysize; int entrysize; int /*<<< orphan*/  hcxt; } ;
struct TYPE_13__ {int mt_nplans; TYPE_2__* resultRelInfo; } ;
struct TYPE_12__ {int /*<<< orphan*/  partition_root; int /*<<< orphan*/ * subplan_resultrel_htab; } ;
struct TYPE_11__ {int /*<<< orphan*/  ri_PartitionRoot; int /*<<< orphan*/  ri_RelationDesc; } ;
struct TYPE_10__ {TYPE_2__* rri; } ;
typedef  TYPE_1__ SubplanResultRelHashElem ;
typedef  TYPE_2__ ResultRelInfo ;
typedef  TYPE_3__ PartitionTupleRouting ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_4__ ModifyTableState ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_5__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int HASH_BLOBS ; 
 int HASH_CONTEXT ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hash_create (char*,int,TYPE_5__*,int) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ExecHashSubPlanResultRelsByOid(ModifyTableState *mtstate,
							   PartitionTupleRouting *proute)
{
	HASHCTL		ctl;
	HTAB	   *htab;
	int			i;

	memset(&ctl, 0, sizeof(ctl));
	ctl.keysize = sizeof(Oid);
	ctl.entrysize = sizeof(SubplanResultRelHashElem);
	ctl.hcxt = CurrentMemoryContext;

	htab = hash_create("PartitionTupleRouting table", mtstate->mt_nplans,
					   &ctl, HASH_ELEM | HASH_BLOBS | HASH_CONTEXT);
	proute->subplan_resultrel_htab = htab;

	/* Hash all subplans by their Oid */
	for (i = 0; i < mtstate->mt_nplans; i++)
	{
		ResultRelInfo *rri = &mtstate->resultRelInfo[i];
		bool		found;
		Oid			partoid = RelationGetRelid(rri->ri_RelationDesc);
		SubplanResultRelHashElem *elem;

		elem = (SubplanResultRelHashElem *)
			hash_search(htab, &partoid, HASH_ENTER, &found);
		Assert(!found);
		elem->rri = rri;

		/*
		 * This is required in order to convert the partition's tuple to be
		 * compatible with the root partitioned table's tuple descriptor. When
		 * generating the per-subplan result rels, this was not set.
		 */
		rri->ri_PartitionRoot = proute->partition_root;
	}
}