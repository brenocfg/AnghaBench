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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_description_classoid ; 
 int /*<<< orphan*/  Anum_pg_description_description ; 
 int /*<<< orphan*/  Anum_pg_description_objoid ; 
 int /*<<< orphan*/  Anum_pg_description_objsubid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  DescriptionObjIndexId ; 
 int /*<<< orphan*/  DescriptionRelationId ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *
GetComment(Oid oid, Oid classoid, int32 subid)
{
	Relation	description;
	ScanKeyData skey[3];
	SysScanDesc sd;
	TupleDesc	tupdesc;
	HeapTuple	tuple;
	char	   *comment;

	/* Use the index to search for a matching old tuple */

	ScanKeyInit(&skey[0],
				Anum_pg_description_objoid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(oid));
	ScanKeyInit(&skey[1],
				Anum_pg_description_classoid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(classoid));
	ScanKeyInit(&skey[2],
				Anum_pg_description_objsubid,
				BTEqualStrategyNumber, F_INT4EQ,
				Int32GetDatum(subid));

	description = table_open(DescriptionRelationId, AccessShareLock);
	tupdesc = RelationGetDescr(description);

	sd = systable_beginscan(description, DescriptionObjIndexId, true,
							NULL, 3, skey);

	comment = NULL;
	while ((tuple = systable_getnext(sd)) != NULL)
	{
		Datum		value;
		bool		isnull;

		/* Found the tuple, get description field */
		value = heap_getattr(tuple, Anum_pg_description_description, tupdesc, &isnull);
		if (!isnull)
			comment = TextDatumGetCString(value);
		break;					/* Assume there can be only one match */
	}

	systable_endscan(sd);

	/* Done */
	table_close(description, AccessShareLock);

	return comment;
}