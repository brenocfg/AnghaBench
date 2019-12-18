#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_5__ ;
typedef  struct TYPE_44__   TYPE_4__ ;
typedef  struct TYPE_43__   TYPE_3__ ;
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_1__ ;
typedef  struct TYPE_40__   TYPE_14__ ;

/* Type definitions */
typedef  TYPE_2__* TupleDesc ;
struct TYPE_45__ {scalar_t__ attisdropped; int /*<<< orphan*/  attname; } ;
struct TYPE_44__ {TYPE_14__* bound; int /*<<< orphan*/  name; } ;
struct TYPE_43__ {int /*<<< orphan*/  trigdesc; int /*<<< orphan*/  rd_islocaltemp; TYPE_1__* rd_rel; } ;
struct TYPE_42__ {int natts; } ;
struct TYPE_41__ {scalar_t__ relkind; scalar_t__ relpersistence; int /*<<< orphan*/  reloftype; scalar_t__ relispartition; } ;
struct TYPE_40__ {int /*<<< orphan*/  is_default; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_3__* Relation ;
typedef  TYPE_4__ PartitionCmd ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_5__* Form_pg_attribute ;
typedef  int AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ATSimplePermissions (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ATTNAME ; 
 int ATT_FOREIGN_TABLE ; 
 int ATT_TABLE ; 
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_inherits_inhparent ; 
 int /*<<< orphan*/  Anum_pg_inherits_inhrelid ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AttachPartitionEnsureIndexes (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CStringGetDatum (char*) ; 
 int /*<<< orphan*/  CloneForeignKeyConstraints (int /*<<< orphan*/ **,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  CloneRowTriggersToPartition (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  CreateInheritance (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_TABLE ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 char* FindTriggerIncompatibleWithInheritance (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InheritsParentIndexId ; 
 int /*<<< orphan*/  InheritsRelationId ; 
 int /*<<< orphan*/  InheritsRelidSeqnoIndexId ; 
 int /*<<< orphan*/  LockRelationOid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QueuePartitionConstraintValidation (int /*<<< orphan*/ **,TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ RELKIND_RELATION ; 
 scalar_t__ RELPERSISTENCE_TEMP ; 
 TYPE_2__* RelationGetDescr (TYPE_3__*) ; 
 int /*<<< orphan*/  RelationGetPartitionDesc (TYPE_3__*) ; 
 int /*<<< orphan*/  RelationGetPartitionQual (TYPE_3__*) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_3__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_3__*) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCacheExists2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StorePartitionBound (TYPE_3__*,TYPE_3__*,TYPE_14__*) ; 
 TYPE_5__* TupleDescAttr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  check_new_partition_bound (int /*<<< orphan*/ ,TYPE_3__*,TYPE_14__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,...) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ eval_const_expressions (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_all_inheritors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_default_oid_from_partdesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_proposed_default_constraint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_qual_from_partbound (TYPE_3__*,TYPE_3__*,TYPE_14__*) ; 
 int /*<<< orphan*/ * list_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_make1 (int /*<<< orphan*/ ) ; 
 scalar_t__ list_member_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_ands_explicit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * map_partition_varattnos (int /*<<< orphan*/ *,int,TYPE_3__*,TYPE_3__*,int*) ; 
 int /*<<< orphan*/  systable_beginscan (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* table_openrv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ObjectAddress
ATExecAttachPartition(List **wqueue, Relation rel, PartitionCmd *cmd)
{
	Relation	attachrel,
				catalog;
	List	   *attachrel_children;
	List	   *partConstraint;
	SysScanDesc scan;
	ScanKeyData skey;
	AttrNumber	attno;
	int			natts;
	TupleDesc	tupleDesc;
	ObjectAddress address;
	const char *trigger_name;
	bool		found_whole_row;
	Oid			defaultPartOid;
	List	   *partBoundConstraint;

	/*
	 * We must lock the default partition if one exists, because attaching a
	 * new partition will change its partition constraint.
	 */
	defaultPartOid =
		get_default_oid_from_partdesc(RelationGetPartitionDesc(rel));
	if (OidIsValid(defaultPartOid))
		LockRelationOid(defaultPartOid, AccessExclusiveLock);

	attachrel = table_openrv(cmd->name, AccessExclusiveLock);

	/*
	 * XXX I think it'd be a good idea to grab locks on all tables referenced
	 * by FKs at this point also.
	 */

	/*
	 * Must be owner of both parent and source table -- parent was checked by
	 * ATSimplePermissions call in ATPrepCmd
	 */
	ATSimplePermissions(attachrel, ATT_TABLE | ATT_FOREIGN_TABLE);

	/* A partition can only have one parent */
	if (attachrel->rd_rel->relispartition)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("\"%s\" is already a partition",
						RelationGetRelationName(attachrel))));

	if (OidIsValid(attachrel->rd_rel->reloftype))
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot attach a typed table as partition")));

	/*
	 * Table being attached should not already be part of inheritance; either
	 * as a child table...
	 */
	catalog = table_open(InheritsRelationId, AccessShareLock);
	ScanKeyInit(&skey,
				Anum_pg_inherits_inhrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(RelationGetRelid(attachrel)));
	scan = systable_beginscan(catalog, InheritsRelidSeqnoIndexId, true,
							  NULL, 1, &skey);
	if (HeapTupleIsValid(systable_getnext(scan)))
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot attach inheritance child as partition")));
	systable_endscan(scan);

	/* ...or as a parent table (except the case when it is partitioned) */
	ScanKeyInit(&skey,
				Anum_pg_inherits_inhparent,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(RelationGetRelid(attachrel)));
	scan = systable_beginscan(catalog, InheritsParentIndexId, true, NULL,
							  1, &skey);
	if (HeapTupleIsValid(systable_getnext(scan)) &&
		attachrel->rd_rel->relkind == RELKIND_RELATION)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot attach inheritance parent as partition")));
	systable_endscan(scan);
	table_close(catalog, AccessShareLock);

	/*
	 * Prevent circularity by seeing if rel is a partition of attachrel. (In
	 * particular, this disallows making a rel a partition of itself.)
	 *
	 * We do that by checking if rel is a member of the list of attachrel's
	 * partitions provided the latter is partitioned at all.  We want to avoid
	 * having to construct this list again, so we request the strongest lock
	 * on all partitions.  We need the strongest lock, because we may decide
	 * to scan them if we find out that the table being attached (or its leaf
	 * partitions) may contain rows that violate the partition constraint. If
	 * the table has a constraint that would prevent such rows, which by
	 * definition is present in all the partitions, we need not scan the
	 * table, nor its partitions.  But we cannot risk a deadlock by taking a
	 * weaker lock now and the stronger one only when needed.
	 */
	attachrel_children = find_all_inheritors(RelationGetRelid(attachrel),
											 AccessExclusiveLock, NULL);
	if (list_member_oid(attachrel_children, RelationGetRelid(rel)))
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_TABLE),
				 errmsg("circular inheritance not allowed"),
				 errdetail("\"%s\" is already a child of \"%s\".",
						   RelationGetRelationName(rel),
						   RelationGetRelationName(attachrel))));

	/* If the parent is permanent, so must be all of its partitions. */
	if (rel->rd_rel->relpersistence != RELPERSISTENCE_TEMP &&
		attachrel->rd_rel->relpersistence == RELPERSISTENCE_TEMP)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot attach a temporary relation as partition of permanent relation \"%s\"",
						RelationGetRelationName(rel))));

	/* Temp parent cannot have a partition that is itself not a temp */
	if (rel->rd_rel->relpersistence == RELPERSISTENCE_TEMP &&
		attachrel->rd_rel->relpersistence != RELPERSISTENCE_TEMP)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot attach a permanent relation as partition of temporary relation \"%s\"",
						RelationGetRelationName(rel))));

	/* If the parent is temp, it must belong to this session */
	if (rel->rd_rel->relpersistence == RELPERSISTENCE_TEMP &&
		!rel->rd_islocaltemp)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot attach as partition of temporary relation of another session")));

	/* Ditto for the partition */
	if (attachrel->rd_rel->relpersistence == RELPERSISTENCE_TEMP &&
		!attachrel->rd_islocaltemp)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot attach temporary relation of another session as partition")));

	/* Check if there are any columns in attachrel that aren't in the parent */
	tupleDesc = RelationGetDescr(attachrel);
	natts = tupleDesc->natts;
	for (attno = 1; attno <= natts; attno++)
	{
		Form_pg_attribute attribute = TupleDescAttr(tupleDesc, attno - 1);
		char	   *attributeName = NameStr(attribute->attname);

		/* Ignore dropped */
		if (attribute->attisdropped)
			continue;

		/* Try to find the column in parent (matching on column name) */
		if (!SearchSysCacheExists2(ATTNAME,
								   ObjectIdGetDatum(RelationGetRelid(rel)),
								   CStringGetDatum(attributeName)))
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("table \"%s\" contains column \"%s\" not found in parent \"%s\"",
							RelationGetRelationName(attachrel), attributeName,
							RelationGetRelationName(rel)),
					 errdetail("The new partition may contain only the columns present in parent.")));
	}

	/*
	 * If child_rel has row-level triggers with transition tables, we
	 * currently don't allow it to become a partition.  See also prohibitions
	 * in ATExecAddInherit() and CreateTrigger().
	 */
	trigger_name = FindTriggerIncompatibleWithInheritance(attachrel->trigdesc);
	if (trigger_name != NULL)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("trigger \"%s\" prevents table \"%s\" from becoming a partition",
						trigger_name, RelationGetRelationName(attachrel)),
				 errdetail("ROW triggers with transition tables are not supported on partitions")));

	/*
	 * Check that the new partition's bound is valid and does not overlap any
	 * of existing partitions of the parent - note that it does not return on
	 * error.
	 */
	check_new_partition_bound(RelationGetRelationName(attachrel), rel,
							  cmd->bound);

	/* OK to create inheritance.  Rest of the checks performed there */
	CreateInheritance(attachrel, rel);

	/* Update the pg_class entry. */
	StorePartitionBound(attachrel, rel, cmd->bound);

	/* Ensure there exists a correct set of indexes in the partition. */
	AttachPartitionEnsureIndexes(rel, attachrel);

	/* and triggers */
	CloneRowTriggersToPartition(rel, attachrel);

	/*
	 * Clone foreign key constraints.  Callee is responsible for setting up
	 * for phase 3 constraint verification.
	 */
	CloneForeignKeyConstraints(wqueue, rel, attachrel);

	/*
	 * Generate partition constraint from the partition bound specification.
	 * If the parent itself is a partition, make sure to include its
	 * constraint as well.
	 */
	partBoundConstraint = get_qual_from_partbound(attachrel, rel, cmd->bound);
	partConstraint = list_concat(partBoundConstraint,
								 RelationGetPartitionQual(rel));

	/* Skip validation if there are no constraints to validate. */
	if (partConstraint)
	{
		/*
		 * Run the partition quals through const-simplification similar to
		 * check constraints.  We skip canonicalize_qual, though, because
		 * partition quals should be in canonical form already.
		 */
		partConstraint =
			(List *) eval_const_expressions(NULL,
											(Node *) partConstraint);

		/* XXX this sure looks wrong */
		partConstraint = list_make1(make_ands_explicit(partConstraint));

		/*
		 * Adjust the generated constraint to match this partition's attribute
		 * numbers.
		 */
		partConstraint = map_partition_varattnos(partConstraint, 1, attachrel,
												 rel, &found_whole_row);
		/* There can never be a whole-row reference here */
		if (found_whole_row)
			elog(ERROR,
				 "unexpected whole-row reference found in partition key");

		/* Validate partition constraints against the table being attached. */
		QueuePartitionConstraintValidation(wqueue, attachrel, partConstraint,
										   false);
	}

	/*
	 * If we're attaching a partition other than the default partition and a
	 * default one exists, then that partition's partition constraint changes,
	 * so add an entry to the work queue to validate it, too.  (We must not do
	 * this when the partition being attached is the default one; we already
	 * did it above!)
	 */
	if (OidIsValid(defaultPartOid))
	{
		Relation	defaultrel;
		List	   *defPartConstraint;

		Assert(!cmd->bound->is_default);

		/* we already hold a lock on the default partition */
		defaultrel = table_open(defaultPartOid, NoLock);
		defPartConstraint =
			get_proposed_default_constraint(partBoundConstraint);

		/*
		 * Map the Vars in the constraint expression from rel's attnos to
		 * defaultrel's.
		 */
		defPartConstraint =
			map_partition_varattnos(defPartConstraint,
									1, defaultrel, rel, NULL);
		QueuePartitionConstraintValidation(wqueue, defaultrel,
										   defPartConstraint, true);

		/* keep our lock until commit. */
		table_close(defaultrel, NoLock);
	}

	ObjectAddressSet(address, RelationRelationId, RelationGetRelid(attachrel));

	/* keep our lock until commit */
	table_close(attachrel, NoLock);

	return address;
}