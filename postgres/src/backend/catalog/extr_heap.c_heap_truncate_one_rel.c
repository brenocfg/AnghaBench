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
struct TYPE_9__ {TYPE_1__* rd_rel; } ;
struct TYPE_8__ {scalar_t__ relkind; int /*<<< orphan*/  reltoastrelid; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 int /*<<< orphan*/  RelationTruncateIndexes (TYPE_2__*) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_relation_nontransactional_truncate (TYPE_2__*) ; 

void
heap_truncate_one_rel(Relation rel)
{
	Oid			toastrelid;

	/*
	 * Truncate the relation.  Partitioned tables have no storage, so there is
	 * nothing to do for them here.
	 */
	if (rel->rd_rel->relkind == RELKIND_PARTITIONED_TABLE)
		return;

	/* Truncate the underlying relation */
	table_relation_nontransactional_truncate(rel);

	/* If the relation has indexes, truncate the indexes too */
	RelationTruncateIndexes(rel);

	/* If there is a toast table, truncate that too */
	toastrelid = rel->rd_rel->reltoastrelid;
	if (OidIsValid(toastrelid))
	{
		Relation	toastrel = table_open(toastrelid, AccessExclusiveLock);

		table_relation_nontransactional_truncate(toastrel);
		RelationTruncateIndexes(toastrel);
		/* keep the lock... */
		table_close(toastrel, NoLock);
	}
}