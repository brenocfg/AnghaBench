#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  relname; } ;
struct TYPE_15__ {int /*<<< orphan*/  trigdesc; TYPE_1__* rd_rel; int /*<<< orphan*/  rd_islocaltemp; } ;
struct TYPE_14__ {scalar_t__ relpersistence; scalar_t__ relkind; scalar_t__ relispartition; } ;
typedef  TYPE_2__* Relation ;
typedef  TYPE_3__ RangeVar ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  ATSimplePermissions (TYPE_2__*,int) ; 
 int ATT_FOREIGN_TABLE ; 
 int ATT_TABLE ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  CreateInheritance (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_TABLE ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 char* FindTriggerIncompatibleWithInheritance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RELPERSISTENCE_TEMP ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  ShareUpdateExclusiveLock ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,...) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/ * find_all_inheritors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ list_member_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_openrv (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ObjectAddress
ATExecAddInherit(Relation child_rel, RangeVar *parent, LOCKMODE lockmode)
{
	Relation	parent_rel;
	List	   *children;
	ObjectAddress address;
	const char *trigger_name;

	/*
	 * A self-exclusive lock is needed here.  See the similar case in
	 * MergeAttributes() for a full explanation.
	 */
	parent_rel = table_openrv(parent, ShareUpdateExclusiveLock);

	/*
	 * Must be owner of both parent and child -- child was checked by
	 * ATSimplePermissions call in ATPrepCmd
	 */
	ATSimplePermissions(parent_rel, ATT_TABLE | ATT_FOREIGN_TABLE);

	/* Permanent rels cannot inherit from temporary ones */
	if (parent_rel->rd_rel->relpersistence == RELPERSISTENCE_TEMP &&
		child_rel->rd_rel->relpersistence != RELPERSISTENCE_TEMP)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot inherit from temporary relation \"%s\"",
						RelationGetRelationName(parent_rel))));

	/* If parent rel is temp, it must belong to this session */
	if (parent_rel->rd_rel->relpersistence == RELPERSISTENCE_TEMP &&
		!parent_rel->rd_islocaltemp)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot inherit from temporary relation of another session")));

	/* Ditto for the child */
	if (child_rel->rd_rel->relpersistence == RELPERSISTENCE_TEMP &&
		!child_rel->rd_islocaltemp)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot inherit to temporary relation of another session")));

	/* Prevent partitioned tables from becoming inheritance parents */
	if (parent_rel->rd_rel->relkind == RELKIND_PARTITIONED_TABLE)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot inherit from partitioned table \"%s\"",
						parent->relname)));

	/* Likewise for partitions */
	if (parent_rel->rd_rel->relispartition)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot inherit from a partition")));

	/*
	 * Prevent circularity by seeing if proposed parent inherits from child.
	 * (In particular, this disallows making a rel inherit from itself.)
	 *
	 * This is not completely bulletproof because of race conditions: in
	 * multi-level inheritance trees, someone else could concurrently be
	 * making another inheritance link that closes the loop but does not join
	 * either of the rels we have locked.  Preventing that seems to require
	 * exclusive locks on the entire inheritance tree, which is a cure worse
	 * than the disease.  find_all_inheritors() will cope with circularity
	 * anyway, so don't sweat it too much.
	 *
	 * We use weakest lock we can on child's children, namely AccessShareLock.
	 */
	children = find_all_inheritors(RelationGetRelid(child_rel),
								   AccessShareLock, NULL);

	if (list_member_oid(children, RelationGetRelid(parent_rel)))
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_TABLE),
				 errmsg("circular inheritance not allowed"),
				 errdetail("\"%s\" is already a child of \"%s\".",
						   parent->relname,
						   RelationGetRelationName(child_rel))));

	/*
	 * If child_rel has row-level triggers with transition tables, we
	 * currently don't allow it to become an inheritance child.  See also
	 * prohibitions in ATExecAttachPartition() and CreateTrigger().
	 */
	trigger_name = FindTriggerIncompatibleWithInheritance(child_rel->trigdesc);
	if (trigger_name != NULL)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("trigger \"%s\" prevents table \"%s\" from becoming an inheritance child",
						trigger_name, RelationGetRelationName(child_rel)),
				 errdetail("ROW triggers with transition tables are not supported in inheritance hierarchies.")));

	/* OK to create inheritance */
	CreateInheritance(child_rel, parent_rel);

	ObjectAddressSet(address, RelationRelationId,
					 RelationGetRelid(parent_rel));

	/* keep our lock on the parent relation until commit */
	table_close(parent_rel, NoLock);

	return address;
}