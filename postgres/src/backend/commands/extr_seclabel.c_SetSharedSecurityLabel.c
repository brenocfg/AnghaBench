#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  replaces ;
typedef  int /*<<< orphan*/  nulls ;
struct TYPE_13__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_12__ {int /*<<< orphan*/  classId; int /*<<< orphan*/  objectId; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ ObjectAddress ;
typedef  TYPE_2__* HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int Anum_pg_shseclabel_classoid ; 
 int Anum_pg_shseclabel_label ; 
 int Anum_pg_shseclabel_objoid ; 
 int Anum_pg_shseclabel_provider ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CStringGetTextDatum (char const*) ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  F_TEXTEQ ; 
 scalar_t__ HeapTupleIsValid (TYPE_2__*) ; 
 int Natts_pg_shseclabel ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SharedSecLabelObjectIndexId ; 
 int /*<<< orphan*/  SharedSecLabelRelationId ; 
 TYPE_2__* heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_2__*) ; 
 TYPE_2__* heap_modify_tuple (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_2__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
SetSharedSecurityLabel(const ObjectAddress *object,
					   const char *provider, const char *label)
{
	Relation	pg_shseclabel;
	ScanKeyData keys[4];
	SysScanDesc scan;
	HeapTuple	oldtup;
	HeapTuple	newtup = NULL;
	Datum		values[Natts_pg_shseclabel];
	bool		nulls[Natts_pg_shseclabel];
	bool		replaces[Natts_pg_shseclabel];

	/* Prepare to form or update a tuple, if necessary. */
	memset(nulls, false, sizeof(nulls));
	memset(replaces, false, sizeof(replaces));
	values[Anum_pg_shseclabel_objoid - 1] = ObjectIdGetDatum(object->objectId);
	values[Anum_pg_shseclabel_classoid - 1] = ObjectIdGetDatum(object->classId);
	values[Anum_pg_shseclabel_provider - 1] = CStringGetTextDatum(provider);
	if (label != NULL)
		values[Anum_pg_shseclabel_label - 1] = CStringGetTextDatum(label);

	/* Use the index to search for a matching old tuple */
	ScanKeyInit(&keys[0],
				Anum_pg_shseclabel_objoid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(object->objectId));
	ScanKeyInit(&keys[1],
				Anum_pg_shseclabel_classoid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(object->classId));
	ScanKeyInit(&keys[2],
				Anum_pg_shseclabel_provider,
				BTEqualStrategyNumber, F_TEXTEQ,
				CStringGetTextDatum(provider));

	pg_shseclabel = table_open(SharedSecLabelRelationId, RowExclusiveLock);

	scan = systable_beginscan(pg_shseclabel, SharedSecLabelObjectIndexId, true,
							  NULL, 3, keys);

	oldtup = systable_getnext(scan);
	if (HeapTupleIsValid(oldtup))
	{
		if (label == NULL)
			CatalogTupleDelete(pg_shseclabel, &oldtup->t_self);
		else
		{
			replaces[Anum_pg_shseclabel_label - 1] = true;
			newtup = heap_modify_tuple(oldtup, RelationGetDescr(pg_shseclabel),
									   values, nulls, replaces);
			CatalogTupleUpdate(pg_shseclabel, &oldtup->t_self, newtup);
		}
	}
	systable_endscan(scan);

	/* If we didn't find an old tuple, insert a new one */
	if (newtup == NULL && label != NULL)
	{
		newtup = heap_form_tuple(RelationGetDescr(pg_shseclabel),
								 values, nulls);
		CatalogTupleInsert(pg_shseclabel, newtup);
	}

	if (newtup != NULL)
		heap_freetuple(newtup);

	table_close(pg_shseclabel, RowExclusiveLock);
}