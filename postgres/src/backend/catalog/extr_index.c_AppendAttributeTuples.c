#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_4__ {int attnum; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  CatalogIndexState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AttributeRelationId ; 
 int /*<<< orphan*/  CatalogCloseIndexes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogOpenIndexes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertPgAttributeTuple (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* TupleDescAttr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AppendAttributeTuples(Relation indexRelation, int numatts)
{
	Relation	pg_attribute;
	CatalogIndexState indstate;
	TupleDesc	indexTupDesc;
	int			i;

	/*
	 * open the attribute relation and its indexes
	 */
	pg_attribute = table_open(AttributeRelationId, RowExclusiveLock);

	indstate = CatalogOpenIndexes(pg_attribute);

	/*
	 * insert data from new index's tupdesc into pg_attribute
	 */
	indexTupDesc = RelationGetDescr(indexRelation);

	for (i = 0; i < numatts; i++)
	{
		Form_pg_attribute attr = TupleDescAttr(indexTupDesc, i);

		Assert(attr->attnum == i + 1);

		InsertPgAttributeTuple(pg_attribute, attr, indstate);
	}

	CatalogCloseIndexes(indstate);

	table_close(pg_attribute, RowExclusiveLock);
}