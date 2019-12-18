#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int Anum_pg_shdescription_classoid ; 
 int Anum_pg_shdescription_description ; 
 int Anum_pg_shdescription_objoid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CStringGetTextDatum (char const*) ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int Natts_pg_shdescription ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SharedDescriptionObjIndexId ; 
 int /*<<< orphan*/  SharedDescriptionRelationId ; 
 TYPE_1__* heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_1__*) ; 
 TYPE_1__* heap_modify_tuple (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_1__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
CreateSharedComments(Oid oid, Oid classoid, const char *comment)
{
	Relation	shdescription;
	ScanKeyData skey[2];
	SysScanDesc sd;
	HeapTuple	oldtuple;
	HeapTuple	newtuple = NULL;
	Datum		values[Natts_pg_shdescription];
	bool		nulls[Natts_pg_shdescription];
	bool		replaces[Natts_pg_shdescription];
	int			i;

	/* Reduce empty-string to NULL case */
	if (comment != NULL && strlen(comment) == 0)
		comment = NULL;

	/* Prepare to form or update a tuple, if necessary */
	if (comment != NULL)
	{
		for (i = 0; i < Natts_pg_shdescription; i++)
		{
			nulls[i] = false;
			replaces[i] = true;
		}
		values[Anum_pg_shdescription_objoid - 1] = ObjectIdGetDatum(oid);
		values[Anum_pg_shdescription_classoid - 1] = ObjectIdGetDatum(classoid);
		values[Anum_pg_shdescription_description - 1] = CStringGetTextDatum(comment);
	}

	/* Use the index to search for a matching old tuple */

	ScanKeyInit(&skey[0],
				Anum_pg_shdescription_objoid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(oid));
	ScanKeyInit(&skey[1],
				Anum_pg_shdescription_classoid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(classoid));

	shdescription = table_open(SharedDescriptionRelationId, RowExclusiveLock);

	sd = systable_beginscan(shdescription, SharedDescriptionObjIndexId, true,
							NULL, 2, skey);

	while ((oldtuple = systable_getnext(sd)) != NULL)
	{
		/* Found the old tuple, so delete or update it */

		if (comment == NULL)
			CatalogTupleDelete(shdescription, &oldtuple->t_self);
		else
		{
			newtuple = heap_modify_tuple(oldtuple, RelationGetDescr(shdescription),
										 values, nulls, replaces);
			CatalogTupleUpdate(shdescription, &oldtuple->t_self, newtuple);
		}

		break;					/* Assume there can be only one match */
	}

	systable_endscan(sd);

	/* If we didn't find an old tuple, insert a new one */

	if (newtuple == NULL && comment != NULL)
	{
		newtuple = heap_form_tuple(RelationGetDescr(shdescription),
								   values, nulls);
		CatalogTupleInsert(shdescription, newtuple);
	}

	if (newtuple != NULL)
		heap_freetuple(newtuple);

	/* Done */

	table_close(shdescription, NoLock);
}