#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  SQLDropList; int /*<<< orphan*/  cxt; } ;
struct TYPE_11__ {scalar_t__ classId; scalar_t__ objectSubId; int /*<<< orphan*/  objectId; } ;
struct TYPE_10__ {int original; int normal; char* schemaname; int istemp; int /*<<< orphan*/  next; TYPE_2__ address; int /*<<< orphan*/  objecttype; int /*<<< orphan*/  addrargs; int /*<<< orphan*/  addrnames; int /*<<< orphan*/  objidentity; int /*<<< orphan*/  objname; } ;
typedef  TYPE_1__ SQLDropObject ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  scalar_t__ HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DatumGetName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetObjectId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EventTriggerSupportsObjectClass (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidAttrNumber ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ NamespaceRelationId ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 TYPE_8__* currentEventTriggerState ; 
 int /*<<< orphan*/  getObjectClass (TYPE_2__ const*) ; 
 int /*<<< orphan*/  getObjectIdentityParts (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getObjectTypeDescription (TYPE_2__*) ; 
 scalar_t__ get_catalog_object_by_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 scalar_t__ get_object_attnum_name (scalar_t__) ; 
 scalar_t__ get_object_attnum_namespace (scalar_t__) ; 
 int /*<<< orphan*/  get_object_attnum_oid (scalar_t__) ; 
 scalar_t__ get_object_namensp_unique (scalar_t__) ; 
 int /*<<< orphan*/  heap_getattr (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ isAnyTempNamespace (int /*<<< orphan*/ ) ; 
 scalar_t__ isTempNamespace (int /*<<< orphan*/ ) ; 
 scalar_t__ is_objectclass_supported (scalar_t__) ; 
 TYPE_1__* palloc0 (int) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 int /*<<< orphan*/  pstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slist_push_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (scalar_t__,int /*<<< orphan*/ ) ; 

void
EventTriggerSQLDropAddObject(const ObjectAddress *object, bool original, bool normal)
{
	SQLDropObject *obj;
	MemoryContext oldcxt;

	if (!currentEventTriggerState)
		return;

	Assert(EventTriggerSupportsObjectClass(getObjectClass(object)));

	/* don't report temp schemas except my own */
	if (object->classId == NamespaceRelationId &&
		(isAnyTempNamespace(object->objectId) &&
		 !isTempNamespace(object->objectId)))
		return;

	oldcxt = MemoryContextSwitchTo(currentEventTriggerState->cxt);

	obj = palloc0(sizeof(SQLDropObject));
	obj->address = *object;
	obj->original = original;
	obj->normal = normal;

	/*
	 * Obtain schema names from the object's catalog tuple, if one exists;
	 * this lets us skip objects in temp schemas.  We trust that
	 * ObjectProperty contains all object classes that can be
	 * schema-qualified.
	 */
	if (is_objectclass_supported(object->classId))
	{
		Relation	catalog;
		HeapTuple	tuple;

		catalog = table_open(obj->address.classId, AccessShareLock);
		tuple = get_catalog_object_by_oid(catalog,
										  get_object_attnum_oid(object->classId),
										  obj->address.objectId);

		if (tuple)
		{
			AttrNumber	attnum;
			Datum		datum;
			bool		isnull;

			attnum = get_object_attnum_namespace(obj->address.classId);
			if (attnum != InvalidAttrNumber)
			{
				datum = heap_getattr(tuple, attnum,
									 RelationGetDescr(catalog), &isnull);
				if (!isnull)
				{
					Oid			namespaceId;

					namespaceId = DatumGetObjectId(datum);
					/* temp objects are only reported if they are my own */
					if (isTempNamespace(namespaceId))
					{
						obj->schemaname = "pg_temp";
						obj->istemp = true;
					}
					else if (isAnyTempNamespace(namespaceId))
					{
						pfree(obj);
						table_close(catalog, AccessShareLock);
						MemoryContextSwitchTo(oldcxt);
						return;
					}
					else
					{
						obj->schemaname = get_namespace_name(namespaceId);
						obj->istemp = false;
					}
				}
			}

			if (get_object_namensp_unique(obj->address.classId) &&
				obj->address.objectSubId == 0)
			{
				attnum = get_object_attnum_name(obj->address.classId);
				if (attnum != InvalidAttrNumber)
				{
					datum = heap_getattr(tuple, attnum,
										 RelationGetDescr(catalog), &isnull);
					if (!isnull)
						obj->objname = pstrdup(NameStr(*DatumGetName(datum)));
				}
			}
		}

		table_close(catalog, AccessShareLock);
	}
	else
	{
		if (object->classId == NamespaceRelationId &&
			isTempNamespace(object->objectId))
			obj->istemp = true;
	}

	/* object identity, objname and objargs */
	obj->objidentity =
		getObjectIdentityParts(&obj->address, &obj->addrnames, &obj->addrargs);

	/* object type */
	obj->objecttype = getObjectTypeDescription(&obj->address);

	slist_push_head(&(currentEventTriggerState->SQLDropList), &obj->next);

	MemoryContextSwitchTo(oldcxt);
}