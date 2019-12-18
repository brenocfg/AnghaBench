#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ ev_class; int /*<<< orphan*/  oid; int /*<<< orphan*/  ev_enabled; } ;
struct TYPE_8__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_rewrite ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CacheInvalidateRelcache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  CharGetDatum (char) ; 
 char DatumGetChar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  PointerGetDatum (char const*) ; 
 int /*<<< orphan*/  RULERELNAME ; 
 scalar_t__ RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RewriteRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCacheCopy2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aclcheck_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_name (scalar_t__) ; 
 int /*<<< orphan*/  get_rel_relkind (scalar_t__) ; 
 int /*<<< orphan*/  get_relkind_objtype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_1__*) ; 
 int /*<<< orphan*/  pg_class_ownercheck (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
EnableDisableRule(Relation rel, const char *rulename,
				  char fires_when)
{
	Relation	pg_rewrite_desc;
	Oid			owningRel = RelationGetRelid(rel);
	Oid			eventRelationOid;
	HeapTuple	ruletup;
	Form_pg_rewrite ruleform;
	bool		changed = false;

	/*
	 * Find the rule tuple to change.
	 */
	pg_rewrite_desc = table_open(RewriteRelationId, RowExclusiveLock);
	ruletup = SearchSysCacheCopy2(RULERELNAME,
								  ObjectIdGetDatum(owningRel),
								  PointerGetDatum(rulename));
	if (!HeapTupleIsValid(ruletup))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("rule \"%s\" for relation \"%s\" does not exist",
						rulename, get_rel_name(owningRel))));

	ruleform = (Form_pg_rewrite) GETSTRUCT(ruletup);

	/*
	 * Verify that the user has appropriate permissions.
	 */
	eventRelationOid = ruleform->ev_class;
	Assert(eventRelationOid == owningRel);
	if (!pg_class_ownercheck(eventRelationOid, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, get_relkind_objtype(get_rel_relkind(eventRelationOid)),
					   get_rel_name(eventRelationOid));

	/*
	 * Change ev_enabled if it is different from the desired new state.
	 */
	if (DatumGetChar(ruleform->ev_enabled) !=
		fires_when)
	{
		ruleform->ev_enabled = CharGetDatum(fires_when);
		CatalogTupleUpdate(pg_rewrite_desc, &ruletup->t_self, ruletup);

		changed = true;
	}

	InvokeObjectPostAlterHook(RewriteRelationId, ruleform->oid, 0);

	heap_freetuple(ruletup);
	table_close(pg_rewrite_desc, RowExclusiveLock);

	/*
	 * If we changed anything, broadcast a SI inval message to force each
	 * backend (including our own!) to rebuild relation's relcache entry.
	 * Otherwise they will fail to apply the change promptly.
	 */
	if (changed)
		CacheInvalidateRelcache(rel);
}