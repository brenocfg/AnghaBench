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
typedef  int /*<<< orphan*/  valuesAtt ;
typedef  int /*<<< orphan*/  replacesAtt ;
typedef  int /*<<< orphan*/  nullsAtt ;
struct TYPE_11__ {int /*<<< orphan*/  atttypmod; int /*<<< orphan*/  atttypid; } ;
struct TYPE_10__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  int Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int Anum_pg_attribute_atthasmissing ; 
 int Anum_pg_attribute_attmissingval ; 
 int /*<<< orphan*/  AttributeRelationId ; 
 int BoolGetDatum (int) ; 
 int /*<<< orphan*/  CStringGetDatum (char*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_ARRAY_IN ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemSet (int*,int,int) ; 
 int Natts_pg_attribute ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int OidFunctionCall3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_1__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCacheAttName (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* heap_modify_tuple (TYPE_1__*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
SetAttrMissing(Oid relid, char *attname, char *value)
{
	Datum		valuesAtt[Natts_pg_attribute];
	bool		nullsAtt[Natts_pg_attribute];
	bool		replacesAtt[Natts_pg_attribute];
	Datum		missingval;
	Form_pg_attribute attStruct;
	Relation	attrrel,
				tablerel;
	HeapTuple	atttup,
				newtup;

	/* lock the table the attribute belongs to */
	tablerel = table_open(relid, AccessExclusiveLock);

	/* Lock the attribute row and get the data */
	attrrel = table_open(AttributeRelationId, RowExclusiveLock);
	atttup = SearchSysCacheAttName(relid, attname);
	if (!HeapTupleIsValid(atttup))
		elog(ERROR, "cache lookup failed for attribute %s of relation %u",
			 attname, relid);
	attStruct = (Form_pg_attribute) GETSTRUCT(atttup);

	/* get an array value from the value string */
	missingval = OidFunctionCall3(F_ARRAY_IN,
								  CStringGetDatum(value),
								  ObjectIdGetDatum(attStruct->atttypid),
								  Int32GetDatum(attStruct->atttypmod));

	/* update the tuple - set atthasmissing and attmissingval */
	MemSet(valuesAtt, 0, sizeof(valuesAtt));
	MemSet(nullsAtt, false, sizeof(nullsAtt));
	MemSet(replacesAtt, false, sizeof(replacesAtt));

	valuesAtt[Anum_pg_attribute_atthasmissing - 1] = BoolGetDatum(true);
	replacesAtt[Anum_pg_attribute_atthasmissing - 1] = true;
	valuesAtt[Anum_pg_attribute_attmissingval - 1] = missingval;
	replacesAtt[Anum_pg_attribute_attmissingval - 1] = true;

	newtup = heap_modify_tuple(atttup, RelationGetDescr(attrrel),
							   valuesAtt, nullsAtt, replacesAtt);
	CatalogTupleUpdate(attrrel, &newtup->t_self, newtup);

	/* clean up */
	ReleaseSysCache(atttup);
	table_close(attrrel, RowExclusiveLock);
	table_close(tablerel, AccessExclusiveLock);
}