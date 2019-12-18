#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int n_members; TYPE_1__** members; } ;
struct TYPE_14__ {int /*<<< orphan*/  enumlabel; } ;
struct TYPE_13__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_12__ {TYPE_2__ tuple; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__* HeapTuple ;
typedef  TYPE_3__* Form_pg_enum ;
typedef  TYPE_4__ CatCList ;

/* Variables and functions */
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ENUMTYPOIDNAME ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERRCODE_INVALID_NAME ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EnumRelationId ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 scalar_t__ GETSTRUCT (TYPE_2__*) ; 
 int /*<<< orphan*/  LockDatabaseObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NAMEDATALEN ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCatCacheList (TYPE_4__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_4__* SearchSysCacheList1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TypeRelationId ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 TYPE_2__* heap_copytuple (TYPE_2__*) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_2__*) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RenameEnumLabel(Oid enumTypeOid,
				const char *oldVal,
				const char *newVal)
{
	Relation	pg_enum;
	HeapTuple	enum_tup;
	Form_pg_enum en;
	CatCList   *list;
	int			nelems;
	HeapTuple	old_tup;
	bool		found_new;
	int			i;

	/* check length of new label is ok */
	if (strlen(newVal) > (NAMEDATALEN - 1))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_NAME),
				 errmsg("invalid enum label \"%s\"", newVal),
				 errdetail("Labels must be %d characters or less.",
						   NAMEDATALEN - 1)));

	/*
	 * Acquire a lock on the enum type, which we won't release until commit.
	 * This ensures that two backends aren't concurrently modifying the same
	 * enum type.  Since we are not changing the type's sort order, this is
	 * probably not really necessary, but there seems no reason not to take
	 * the lock to be sure.
	 */
	LockDatabaseObject(TypeRelationId, enumTypeOid, 0, ExclusiveLock);

	pg_enum = table_open(EnumRelationId, RowExclusiveLock);

	/* Get the list of existing members of the enum */
	list = SearchSysCacheList1(ENUMTYPOIDNAME,
							   ObjectIdGetDatum(enumTypeOid));
	nelems = list->n_members;

	/*
	 * Locate the element to rename and check if the new label is already in
	 * use.  (The unique index on pg_enum would catch that anyway, but we
	 * prefer a friendlier error message.)
	 */
	old_tup = NULL;
	found_new = false;
	for (i = 0; i < nelems; i++)
	{
		enum_tup = &(list->members[i]->tuple);
		en = (Form_pg_enum) GETSTRUCT(enum_tup);
		if (strcmp(NameStr(en->enumlabel), oldVal) == 0)
			old_tup = enum_tup;
		if (strcmp(NameStr(en->enumlabel), newVal) == 0)
			found_new = true;
	}
	if (!old_tup)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("\"%s\" is not an existing enum label",
						oldVal)));
	if (found_new)
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("enum label \"%s\" already exists",
						newVal)));

	/* OK, make a writable copy of old tuple */
	enum_tup = heap_copytuple(old_tup);
	en = (Form_pg_enum) GETSTRUCT(enum_tup);

	ReleaseCatCacheList(list);

	/* Update the pg_enum entry */
	namestrcpy(&en->enumlabel, newVal);
	CatalogTupleUpdate(pg_enum, &enum_tup->t_self, enum_tup);
	heap_freetuple(enum_tup);

	table_close(pg_enum, RowExclusiveLock);
}