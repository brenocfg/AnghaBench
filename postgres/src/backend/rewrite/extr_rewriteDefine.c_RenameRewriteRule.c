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
struct TYPE_9__ {scalar_t__ ev_type; int /*<<< orphan*/  rulename; int /*<<< orphan*/  oid; } ;
struct TYPE_8__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  RangeVar ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_rewrite ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 scalar_t__ CMD_SELECT ; 
 int /*<<< orphan*/  CacheInvalidateRelcache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERRCODE_INVALID_OBJECT_DEFINITION ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 scalar_t__ IsDefinedRewriteRule (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (char const*) ; 
 int /*<<< orphan*/  RULERELNAME ; 
 int /*<<< orphan*/  RangeVarCallbackForRenameRule ; 
 int /*<<< orphan*/  RangeVarGetRelidExtended (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RewriteRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCacheCopy2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_1__*) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ObjectAddress
RenameRewriteRule(RangeVar *relation, const char *oldName,
				  const char *newName)
{
	Oid			relid;
	Relation	targetrel;
	Relation	pg_rewrite_desc;
	HeapTuple	ruletup;
	Form_pg_rewrite ruleform;
	Oid			ruleOid;
	ObjectAddress address;

	/*
	 * Look up name, check permissions, and acquire lock (which we will NOT
	 * release until end of transaction).
	 */
	relid = RangeVarGetRelidExtended(relation, AccessExclusiveLock,
									 0,
									 RangeVarCallbackForRenameRule,
									 NULL);

	/* Have lock already, so just need to build relcache entry. */
	targetrel = relation_open(relid, NoLock);

	/* Prepare to modify pg_rewrite */
	pg_rewrite_desc = table_open(RewriteRelationId, RowExclusiveLock);

	/* Fetch the rule's entry (it had better exist) */
	ruletup = SearchSysCacheCopy2(RULERELNAME,
								  ObjectIdGetDatum(relid),
								  PointerGetDatum(oldName));
	if (!HeapTupleIsValid(ruletup))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("rule \"%s\" for relation \"%s\" does not exist",
						oldName, RelationGetRelationName(targetrel))));
	ruleform = (Form_pg_rewrite) GETSTRUCT(ruletup);
	ruleOid = ruleform->oid;

	/* rule with the new name should not already exist */
	if (IsDefinedRewriteRule(relid, newName))
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("rule \"%s\" for relation \"%s\" already exists",
						newName, RelationGetRelationName(targetrel))));

	/*
	 * We disallow renaming ON SELECT rules, because they should always be
	 * named "_RETURN".
	 */
	if (ruleform->ev_type == CMD_SELECT + '0')
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
				 errmsg("renaming an ON SELECT rule is not allowed")));

	/* OK, do the update */
	namestrcpy(&(ruleform->rulename), newName);

	CatalogTupleUpdate(pg_rewrite_desc, &ruletup->t_self, ruletup);

	heap_freetuple(ruletup);
	table_close(pg_rewrite_desc, RowExclusiveLock);

	/*
	 * Invalidate relation's relcache entry so that other backends (and this
	 * one too!) are sent SI message to make them rebuild relcache entries.
	 * (Ideally this should happen automatically...)
	 */
	CacheInvalidateRelcache(targetrel);

	ObjectAddressSet(address, RewriteRelationId, ruleOid);

	/*
	 * Close rel, but keep exclusive lock!
	 */
	relation_close(targetrel, NoLock);

	return address;
}