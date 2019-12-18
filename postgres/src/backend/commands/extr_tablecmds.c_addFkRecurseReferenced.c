#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int int16 ;
struct TYPE_22__ {char* conname; int /*<<< orphan*/  fk_matchtype; int /*<<< orphan*/  fk_del_action; int /*<<< orphan*/  fk_upd_action; int /*<<< orphan*/  initially_valid; int /*<<< orphan*/  initdeferred; int /*<<< orphan*/  deferrable; int /*<<< orphan*/  fk_attrs; } ;
struct TYPE_21__ {int nparts; int /*<<< orphan*/ * oids; } ;
struct TYPE_20__ {TYPE_1__* rd_rel; } ;
struct TYPE_19__ {scalar_t__ relkind; } ;
typedef  TYPE_2__* Relation ;
typedef  TYPE_3__* PartitionDesc ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_4__ Constraint ;
typedef  int AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  CONSTRAINT_FOREIGN ; 
 int /*<<< orphan*/  CONSTRAINT_RELATION ; 
 char* ChooseConstraintName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ChooseForeignKeyConstraintNameAddition (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 scalar_t__ ConstraintNameIsUsed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ConstraintRelationId ; 
 int /*<<< orphan*/  CreateConstraintEntry (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  DEPENDENCY_INTERNAL ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RELKIND_RELATION ; 
 int /*<<< orphan*/  RelationGetDescr (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetNamespace (TYPE_2__*) ; 
 TYPE_3__* RelationGetPartitionDesc (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 int /*<<< orphan*/  ShareRowExclusiveLock ; 
 int* convert_tuples_by_name_map_if_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  createForeignKeyActionTriggers (TYPE_2__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_get_partition (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int* palloc (int) ; 
 int /*<<< orphan*/  pfree (int*) ; 
 int /*<<< orphan*/  recordDependencyOn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ObjectAddress
addFkRecurseReferenced(List **wqueue, Constraint *fkconstraint, Relation rel,
					   Relation pkrel, Oid indexOid, Oid parentConstr,
					   int numfks,
					   int16 *pkattnum, int16 *fkattnum, Oid *pfeqoperators,
					   Oid *ppeqoperators, Oid *ffeqoperators, bool old_check_ok)
{
	ObjectAddress address;
	Oid			constrOid;
	char	   *conname;
	bool		conislocal;
	int			coninhcount;
	bool		connoinherit;

	/*
	 * Verify relkind for each referenced partition.  At the top level, this
	 * is redundant with a previous check, but we need it when recursing.
	 */
	if (pkrel->rd_rel->relkind != RELKIND_RELATION &&
		pkrel->rd_rel->relkind != RELKIND_PARTITIONED_TABLE)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("referenced relation \"%s\" is not a table",
						RelationGetRelationName(pkrel))));

	/*
	 * Caller supplies us with a constraint name; however, it may be used in
	 * this partition, so come up with a different one in that case.
	 */
	if (ConstraintNameIsUsed(CONSTRAINT_RELATION,
							 RelationGetRelid(rel),
							 fkconstraint->conname))
		conname = ChooseConstraintName(RelationGetRelationName(rel),
									   ChooseForeignKeyConstraintNameAddition(fkconstraint->fk_attrs),
									   "fkey",
									   RelationGetNamespace(rel), NIL);
	else
		conname = fkconstraint->conname;

	if (OidIsValid(parentConstr))
	{
		conislocal = false;
		coninhcount = 1;
		connoinherit = false;
	}
	else
	{
		conislocal = true;
		coninhcount = 0;

		/*
		 * always inherit for partitioned tables, never for legacy inheritance
		 */
		connoinherit = rel->rd_rel->relkind != RELKIND_PARTITIONED_TABLE;
	}

	/*
	 * Record the FK constraint in pg_constraint.
	 */
	constrOid = CreateConstraintEntry(conname,
									  RelationGetNamespace(rel),
									  CONSTRAINT_FOREIGN,
									  fkconstraint->deferrable,
									  fkconstraint->initdeferred,
									  fkconstraint->initially_valid,
									  parentConstr,
									  RelationGetRelid(rel),
									  fkattnum,
									  numfks,
									  numfks,
									  InvalidOid,	/* not a domain constraint */
									  indexOid,
									  RelationGetRelid(pkrel),
									  pkattnum,
									  pfeqoperators,
									  ppeqoperators,
									  ffeqoperators,
									  numfks,
									  fkconstraint->fk_upd_action,
									  fkconstraint->fk_del_action,
									  fkconstraint->fk_matchtype,
									  NULL, /* no exclusion constraint */
									  NULL, /* no check constraint */
									  NULL,
									  conislocal,	/* islocal */
									  coninhcount,	/* inhcount */
									  connoinherit, /* conNoInherit */
									  false);	/* is_internal */

	ObjectAddressSet(address, ConstraintRelationId, constrOid);

	/*
	 * Mark the child constraint as part of the parent constraint; it must not
	 * be dropped on its own.  (This constraint is deleted when the partition
	 * is detached, but a special check needs to occur that the partition
	 * contains no referenced values.)
	 */
	if (OidIsValid(parentConstr))
	{
		ObjectAddress referenced;

		ObjectAddressSet(referenced, ConstraintRelationId, parentConstr);
		recordDependencyOn(&address, &referenced, DEPENDENCY_INTERNAL);
	}

	/* make new constraint visible, in case we add more */
	CommandCounterIncrement();

	/*
	 * If the referenced table is a plain relation, create the action triggers
	 * that enforce the constraint.
	 */
	if (pkrel->rd_rel->relkind == RELKIND_RELATION)
	{
		createForeignKeyActionTriggers(rel, RelationGetRelid(pkrel),
									   fkconstraint,
									   constrOid, indexOid);
	}

	/*
	 * If the referenced table is partitioned, recurse on ourselves to handle
	 * each partition.  We need one pg_constraint row created for each
	 * partition in addition to the pg_constraint row for the parent table.
	 */
	if (pkrel->rd_rel->relkind == RELKIND_PARTITIONED_TABLE)
	{
		PartitionDesc pd = RelationGetPartitionDesc(pkrel);

		for (int i = 0; i < pd->nparts; i++)
		{
			Relation	partRel;
			AttrNumber *map;
			AttrNumber *mapped_pkattnum;
			Oid			partIndexId;

			partRel = table_open(pd->oids[i], ShareRowExclusiveLock);

			/*
			 * Map the attribute numbers in the referenced side of the FK
			 * definition to match the partition's column layout.
			 */
			map = convert_tuples_by_name_map_if_req(RelationGetDescr(partRel),
													RelationGetDescr(pkrel));
			if (map)
			{
				mapped_pkattnum = palloc(sizeof(AttrNumber) * numfks);
				for (int j = 0; j < numfks; j++)
					mapped_pkattnum[j] = map[pkattnum[j] - 1];
			}
			else
				mapped_pkattnum = pkattnum;

			/* do the deed */
			partIndexId = index_get_partition(partRel, indexOid);
			if (!OidIsValid(partIndexId))
				elog(ERROR, "index for %u not found in partition %s",
					 indexOid, RelationGetRelationName(partRel));
			addFkRecurseReferenced(wqueue, fkconstraint, rel, partRel,
								   partIndexId, constrOid, numfks,
								   mapped_pkattnum, fkattnum,
								   pfeqoperators, ppeqoperators, ffeqoperators,
								   old_check_ok);

			/* Done -- clean up (but keep the lock) */
			table_close(partRel, NoLock);
			if (map)
			{
				pfree(mapped_pkattnum);
				pfree(map);
			}
		}
	}

	return address;
}