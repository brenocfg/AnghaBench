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
typedef  int /*<<< orphan*/  nulls ;
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int Anum_pg_inherits_inhparent ; 
 int Anum_pg_inherits_inhrelid ; 
 int Anum_pg_inherits_inhseqno ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InheritsRelationId ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int Natts_pg_inherits ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
StoreSingleInheritance(Oid relationId, Oid parentOid, int32 seqNumber)
{
	Datum		values[Natts_pg_inherits];
	bool		nulls[Natts_pg_inherits];
	HeapTuple	tuple;
	Relation	inhRelation;

	inhRelation = table_open(InheritsRelationId, RowExclusiveLock);

	/*
	 * Make the pg_inherits entry
	 */
	values[Anum_pg_inherits_inhrelid - 1] = ObjectIdGetDatum(relationId);
	values[Anum_pg_inherits_inhparent - 1] = ObjectIdGetDatum(parentOid);
	values[Anum_pg_inherits_inhseqno - 1] = Int32GetDatum(seqNumber);

	memset(nulls, 0, sizeof(nulls));

	tuple = heap_form_tuple(RelationGetDescr(inhRelation), values, nulls);

	CatalogTupleInsert(inhRelation, tuple);

	heap_freetuple(tuple);

	table_close(inhRelation, RowExclusiveLock);
}