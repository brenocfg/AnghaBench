#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_17__ ;
typedef  struct TYPE_25__   TYPE_16__ ;
typedef  struct TYPE_24__   TYPE_15__ ;
typedef  struct TYPE_23__   TYPE_14__ ;
typedef  struct TYPE_22__   TYPE_13__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_31__ {int /*<<< orphan*/  name; TYPE_4__* namespace; } ;
struct TYPE_20__ {TYPE_5__ dobj; } ;
typedef  TYPE_11__ TypeInfo ;
struct TYPE_21__ {TYPE_9__* tgtable; } ;
typedef  TYPE_12__ TriggerInfo ;
struct TYPE_34__ {int /*<<< orphan*/  name; } ;
struct TYPE_35__ {TYPE_8__ dobj; } ;
struct TYPE_32__ {int /*<<< orphan*/  name; } ;
struct TYPE_33__ {TYPE_6__ dobj; } ;
struct TYPE_29__ {int /*<<< orphan*/  name; } ;
struct TYPE_30__ {TYPE_3__ dobj; } ;
struct TYPE_27__ {int /*<<< orphan*/  name; } ;
struct TYPE_28__ {TYPE_1__ dobj; } ;
struct TYPE_26__ {int adnum; } ;
struct TYPE_19__ {int /*<<< orphan*/  oid; } ;
struct TYPE_25__ {size_t objType; TYPE_10__ catId; int /*<<< orphan*/  name; TYPE_2__* namespace; } ;
struct TYPE_24__ {int nargs; int /*<<< orphan*/ * argtypes; } ;
struct TYPE_23__ {int oprkind; } ;
struct TYPE_22__ {TYPE_7__* poltable; } ;
typedef  TYPE_13__ PolicyInfo ;
typedef  TYPE_14__ OprInfo ;
typedef  TYPE_15__ FuncInfo ;
typedef  TYPE_16__ DumpableObject ;
typedef  TYPE_17__ AttrDefInfo ;

/* Variables and functions */
 size_t DO_AGG ; 
 size_t DO_ATTRDEF ; 
 size_t DO_FUNC ; 
 size_t DO_OPERATOR ; 
 size_t DO_POLICY ; 
 size_t DO_TRIGGER ; 
 int* dbObjectTypePriority ; 
 TYPE_11__* findTypeByOid (int /*<<< orphan*/ ) ; 
 int oidcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
DOTypeNameCompare(const void *p1, const void *p2)
{
	DumpableObject *obj1 = *(DumpableObject *const *) p1;
	DumpableObject *obj2 = *(DumpableObject *const *) p2;
	int			cmpval;

	/* Sort by type's priority */
	cmpval = dbObjectTypePriority[obj1->objType] -
		dbObjectTypePriority[obj2->objType];

	if (cmpval != 0)
		return cmpval;

	/*
	 * Sort by namespace.  Typically, all objects of the same priority would
	 * either have or not have a namespace link, but there are exceptions.
	 * Sort NULL namespace after non-NULL in such cases.
	 */
	if (obj1->namespace)
	{
		if (obj2->namespace)
		{
			cmpval = strcmp(obj1->namespace->dobj.name,
							obj2->namespace->dobj.name);
			if (cmpval != 0)
				return cmpval;
		}
		else
			return -1;
	}
	else if (obj2->namespace)
		return 1;

	/* Sort by name */
	cmpval = strcmp(obj1->name, obj2->name);
	if (cmpval != 0)
		return cmpval;

	/* To have a stable sort order, break ties for some object types */
	if (obj1->objType == DO_FUNC || obj1->objType == DO_AGG)
	{
		FuncInfo   *fobj1 = *(FuncInfo *const *) p1;
		FuncInfo   *fobj2 = *(FuncInfo *const *) p2;
		int			i;

		/* Sort by number of arguments, then argument type names */
		cmpval = fobj1->nargs - fobj2->nargs;
		if (cmpval != 0)
			return cmpval;
		for (i = 0; i < fobj1->nargs; i++)
		{
			TypeInfo   *argtype1 = findTypeByOid(fobj1->argtypes[i]);
			TypeInfo   *argtype2 = findTypeByOid(fobj2->argtypes[i]);

			if (argtype1 && argtype2)
			{
				if (argtype1->dobj.namespace && argtype2->dobj.namespace)
				{
					cmpval = strcmp(argtype1->dobj.namespace->dobj.name,
									argtype2->dobj.namespace->dobj.name);
					if (cmpval != 0)
						return cmpval;
				}
				cmpval = strcmp(argtype1->dobj.name, argtype2->dobj.name);
				if (cmpval != 0)
					return cmpval;
			}
		}
	}
	else if (obj1->objType == DO_OPERATOR)
	{
		OprInfo    *oobj1 = *(OprInfo *const *) p1;
		OprInfo    *oobj2 = *(OprInfo *const *) p2;

		/* oprkind is 'l', 'r', or 'b'; this sorts prefix, postfix, infix */
		cmpval = (oobj2->oprkind - oobj1->oprkind);
		if (cmpval != 0)
			return cmpval;
	}
	else if (obj1->objType == DO_ATTRDEF)
	{
		AttrDefInfo *adobj1 = *(AttrDefInfo *const *) p1;
		AttrDefInfo *adobj2 = *(AttrDefInfo *const *) p2;

		/* Sort by attribute number */
		cmpval = (adobj1->adnum - adobj2->adnum);
		if (cmpval != 0)
			return cmpval;
	}
	else if (obj1->objType == DO_POLICY)
	{
		PolicyInfo *pobj1 = *(PolicyInfo *const *) p1;
		PolicyInfo *pobj2 = *(PolicyInfo *const *) p2;

		/* Sort by table name (table namespace was considered already) */
		cmpval = strcmp(pobj1->poltable->dobj.name,
						pobj2->poltable->dobj.name);
		if (cmpval != 0)
			return cmpval;
	}
	else if (obj1->objType == DO_TRIGGER)
	{
		TriggerInfo *tobj1 = *(TriggerInfo *const *) p1;
		TriggerInfo *tobj2 = *(TriggerInfo *const *) p2;

		/* Sort by table name (table namespace was considered already) */
		cmpval = strcmp(tobj1->tgtable->dobj.name,
						tobj2->tgtable->dobj.name);
		if (cmpval != 0)
			return cmpval;
	}

	/* Usually shouldn't get here, but if we do, sort by OID */
	return oidcmp(obj1->catId.oid, obj2->catId.oid);
}