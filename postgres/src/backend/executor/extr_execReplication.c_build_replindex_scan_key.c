#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/ * values; } ;
typedef  TYPE_2__ oidvector ;
struct TYPE_17__ {int* values; } ;
typedef  TYPE_3__ int2vector ;
struct TYPE_18__ {scalar_t__* tts_isnull; int /*<<< orphan*/ * tts_values; } ;
typedef  TYPE_4__ TupleTableSlot ;
struct TYPE_20__ {int /*<<< orphan*/ * rd_indcollation; int /*<<< orphan*/  rd_indextuple; TYPE_1__* rd_index; } ;
struct TYPE_19__ {int /*<<< orphan*/  sk_flags; int /*<<< orphan*/  sk_collation; } ;
struct TYPE_15__ {TYPE_3__ indkey; } ;
typedef  TYPE_5__* ScanKey ;
typedef  TYPE_6__* Relation ;
typedef  int /*<<< orphan*/  RegProcedure ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_index_indclass ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  INDEXRELID ; 
 int IndexRelationGetNumberOfKeyAttributes (TYPE_6__*) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationGetRelid (TYPE_6__*) ; 
 scalar_t__ RelationGetReplicaIndex (TYPE_6__*) ; 
 int /*<<< orphan*/  SK_ISNULL ; 
 int /*<<< orphan*/  ScanKeyInit (TYPE_5__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_opclass_family (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_opclass_input_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_opcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_opfamily_member (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
build_replindex_scan_key(ScanKey skey, Relation rel, Relation idxrel,
						 TupleTableSlot *searchslot)
{
	int			attoff;
	bool		isnull;
	Datum		indclassDatum;
	oidvector  *opclass;
	int2vector *indkey = &idxrel->rd_index->indkey;
	bool		hasnulls = false;

	Assert(RelationGetReplicaIndex(rel) == RelationGetRelid(idxrel));

	indclassDatum = SysCacheGetAttr(INDEXRELID, idxrel->rd_indextuple,
									Anum_pg_index_indclass, &isnull);
	Assert(!isnull);
	opclass = (oidvector *) DatumGetPointer(indclassDatum);

	/* Build scankey for every attribute in the index. */
	for (attoff = 0; attoff < IndexRelationGetNumberOfKeyAttributes(idxrel); attoff++)
	{
		Oid			operator;
		Oid			opfamily;
		RegProcedure regop;
		int			pkattno = attoff + 1;
		int			mainattno = indkey->values[attoff];
		Oid			optype = get_opclass_input_type(opclass->values[attoff]);

		/*
		 * Load the operator info.  We need this to get the equality operator
		 * function for the scan key.
		 */
		opfamily = get_opclass_family(opclass->values[attoff]);

		operator = get_opfamily_member(opfamily, optype,
									   optype,
									   BTEqualStrategyNumber);
		if (!OidIsValid(operator))
			elog(ERROR, "missing operator %d(%u,%u) in opfamily %u",
				 BTEqualStrategyNumber, optype, optype, opfamily);

		regop = get_opcode(operator);

		/* Initialize the scankey. */
		ScanKeyInit(&skey[attoff],
					pkattno,
					BTEqualStrategyNumber,
					regop,
					searchslot->tts_values[mainattno - 1]);

		skey[attoff].sk_collation = idxrel->rd_indcollation[attoff];

		/* Check for null value. */
		if (searchslot->tts_isnull[mainattno - 1])
		{
			hasnulls = true;
			skey[attoff].sk_flags |= SK_ISNULL;
		}
	}

	return hasnulls;
}