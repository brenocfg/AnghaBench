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
struct TYPE_4__ {int /*<<< orphan*/  objectSubId; int /*<<< orphan*/  classId; int /*<<< orphan*/  objectId; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_seclabel_classoid ; 
 int /*<<< orphan*/  Anum_pg_seclabel_label ; 
 int /*<<< orphan*/  Anum_pg_seclabel_objoid ; 
 int /*<<< orphan*/  Anum_pg_seclabel_objsubid ; 
 int /*<<< orphan*/  Anum_pg_seclabel_provider ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CStringGetTextDatum (char const*) ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  F_TEXTEQ ; 
 char* GetSharedSecurityLabel (TYPE_1__ const*,char const*) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ IsSharedRelation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SecLabelObjectIndexId ; 
 int /*<<< orphan*/  SecLabelRelationId ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *
GetSecurityLabel(const ObjectAddress *object, const char *provider)
{
	Relation	pg_seclabel;
	ScanKeyData keys[4];
	SysScanDesc scan;
	HeapTuple	tuple;
	Datum		datum;
	bool		isnull;
	char	   *seclabel = NULL;

	/* Shared objects have their own security label catalog. */
	if (IsSharedRelation(object->classId))
		return GetSharedSecurityLabel(object, provider);

	/* Must be an unshared object, so examine pg_seclabel. */
	ScanKeyInit(&keys[0],
				Anum_pg_seclabel_objoid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(object->objectId));
	ScanKeyInit(&keys[1],
				Anum_pg_seclabel_classoid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(object->classId));
	ScanKeyInit(&keys[2],
				Anum_pg_seclabel_objsubid,
				BTEqualStrategyNumber, F_INT4EQ,
				Int32GetDatum(object->objectSubId));
	ScanKeyInit(&keys[3],
				Anum_pg_seclabel_provider,
				BTEqualStrategyNumber, F_TEXTEQ,
				CStringGetTextDatum(provider));

	pg_seclabel = table_open(SecLabelRelationId, AccessShareLock);

	scan = systable_beginscan(pg_seclabel, SecLabelObjectIndexId, true,
							  NULL, 4, keys);

	tuple = systable_getnext(scan);
	if (HeapTupleIsValid(tuple))
	{
		datum = heap_getattr(tuple, Anum_pg_seclabel_label,
							 RelationGetDescr(pg_seclabel), &isnull);
		if (!isnull)
			seclabel = TextDatumGetCString(datum);
	}
	systable_endscan(scan);

	table_close(pg_seclabel, AccessShareLock);

	return seclabel;
}