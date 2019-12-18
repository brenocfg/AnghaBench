#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int validate_default; int /*<<< orphan*/ * partition_constraint; } ;
struct TYPE_18__ {int nparts; int /*<<< orphan*/ * oids; } ;
struct TYPE_17__ {TYPE_1__* rd_rel; } ;
struct TYPE_16__ {scalar_t__ relkind; } ;
typedef  TYPE_2__* Relation ;
typedef  TYPE_3__* PartitionDesc ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Expr ;
typedef  TYPE_4__ AlteredTableInfo ;

/* Variables and functions */
 TYPE_4__* ATGetQueueEntry (int /*<<< orphan*/ **,TYPE_2__*) ; 
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ PartConstraintImpliedByRelConstraint (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RELKIND_RELATION ; 
 TYPE_3__* RelationGetPartitionDesc (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * map_partition_varattnos (int /*<<< orphan*/ *,int,TYPE_2__*,TYPE_2__*,int*) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
QueuePartitionConstraintValidation(List **wqueue, Relation scanrel,
								   List *partConstraint,
								   bool validate_default)
{
	/*
	 * Based on the table's existing constraints, determine whether or not we
	 * may skip scanning the table.
	 */
	if (PartConstraintImpliedByRelConstraint(scanrel, partConstraint))
	{
		if (!validate_default)
			ereport(DEBUG1,
					(errmsg("partition constraint for table \"%s\" is implied by existing constraints",
							RelationGetRelationName(scanrel))));
		else
			ereport(DEBUG1,
					(errmsg("updated partition constraint for default partition \"%s\" is implied by existing constraints",
							RelationGetRelationName(scanrel))));
		return;
	}

	/*
	 * Constraints proved insufficient. For plain relations, queue a
	 * validation item now; for partitioned tables, recurse to process each
	 * partition.
	 */
	if (scanrel->rd_rel->relkind == RELKIND_RELATION)
	{
		AlteredTableInfo *tab;

		/* Grab a work queue entry. */
		tab = ATGetQueueEntry(wqueue, scanrel);
		Assert(tab->partition_constraint == NULL);
		tab->partition_constraint = (Expr *) linitial(partConstraint);
		tab->validate_default = validate_default;
	}
	else if (scanrel->rd_rel->relkind == RELKIND_PARTITIONED_TABLE)
	{
		PartitionDesc partdesc = RelationGetPartitionDesc(scanrel);
		int			i;

		for (i = 0; i < partdesc->nparts; i++)
		{
			Relation	part_rel;
			bool		found_whole_row;
			List	   *thisPartConstraint;

			/*
			 * This is the minimum lock we need to prevent deadlocks.
			 */
			part_rel = table_open(partdesc->oids[i], AccessExclusiveLock);

			/*
			 * Adjust the constraint for scanrel so that it matches this
			 * partition's attribute numbers.
			 */
			thisPartConstraint =
				map_partition_varattnos(partConstraint, 1,
										part_rel, scanrel, &found_whole_row);
			/* There can never be a whole-row reference here */
			if (found_whole_row)
				elog(ERROR, "unexpected whole-row reference found in partition constraint");

			QueuePartitionConstraintValidation(wqueue, part_rel,
											   thisPartConstraint,
											   validate_default);
			table_close(part_rel, NoLock);	/* keep lock till commit */
		}
	}
}