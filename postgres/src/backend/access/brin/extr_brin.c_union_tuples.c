#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ * rd_indcollation; } ;
struct TYPE_13__ {TYPE_2__* bt_columns; } ;
struct TYPE_12__ {TYPE_7__* bd_index; TYPE_1__* bd_tupdesc; } ;
struct TYPE_11__ {int natts; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  TYPE_2__ BrinValues ;
typedef  int /*<<< orphan*/  BrinTuple ;
typedef  TYPE_3__ BrinMemTuple ;
typedef  TYPE_2__ BrinDesc ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRIN_PROCNUM_UNION ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  FunctionCall3Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_2__*) ; 
 TYPE_3__* brin_deform_tuple (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * index_getprocinfo (TYPE_7__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
union_tuples(BrinDesc *bdesc, BrinMemTuple *a, BrinTuple *b)
{
	int			keyno;
	BrinMemTuple *db;
	MemoryContext cxt;
	MemoryContext oldcxt;

	/* Use our own memory context to avoid retail pfree */
	cxt = AllocSetContextCreate(CurrentMemoryContext,
								"brin union",
								ALLOCSET_DEFAULT_SIZES);
	oldcxt = MemoryContextSwitchTo(cxt);
	db = brin_deform_tuple(bdesc, b, NULL);
	MemoryContextSwitchTo(oldcxt);

	for (keyno = 0; keyno < bdesc->bd_tupdesc->natts; keyno++)
	{
		FmgrInfo   *unionFn;
		BrinValues *col_a = &a->bt_columns[keyno];
		BrinValues *col_b = &db->bt_columns[keyno];

		unionFn = index_getprocinfo(bdesc->bd_index, keyno + 1,
									BRIN_PROCNUM_UNION);
		FunctionCall3Coll(unionFn,
						  bdesc->bd_index->rd_indcollation[keyno],
						  PointerGetDatum(bdesc),
						  PointerGetDatum(col_a),
						  PointerGetDatum(col_b));
	}

	MemoryContextDelete(cxt);
}