#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ TransactionId ;
struct TYPE_28__ {scalar_t__ relfrozenxid; scalar_t__ relminmxid; char relpersistence; scalar_t__ relallvisible; scalar_t__ reltuples; scalar_t__ relpages; void* relfilenode; } ;
struct TYPE_27__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_26__ {void* relNode; } ;
struct TYPE_25__ {int /*<<< orphan*/  rd_newRelfilenodeSubid; TYPE_1__* rd_rel; TYPE_3__ rd_node; } ;
struct TYPE_24__ {int relkind; int /*<<< orphan*/  relisshared; int /*<<< orphan*/  reltablespace; } ;
typedef  int /*<<< orphan*/  SMgrRelation ;
typedef  TYPE_2__* Relation ;
typedef  TYPE_3__ RelFileNode ;
typedef  void* Oid ;
typedef  scalar_t__ MultiXactId ;
typedef  TYPE_4__* HeapTuple ;
typedef  TYPE_5__* Form_pg_class ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CacheInvalidateRelcache (TYPE_2__*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (TYPE_2__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  EOXactListAdd (TYPE_2__*) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_4__*) ; 
 int /*<<< orphan*/  GetCurrentSubTransactionId () ; 
 int /*<<< orphan*/  GetCurrentTransactionId () ; 
 void* GetNewRelFileNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_4__*) ; 
 scalar_t__ InvalidMultiXactId ; 
 scalar_t__ InvalidTransactionId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
#define  RELKIND_INDEX 132 
#define  RELKIND_MATVIEW 131 
#define  RELKIND_RELATION 130 
#define  RELKIND_SEQUENCE 129 
#define  RELKIND_TOASTVALUE 128 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  RelationCreateStorage (TYPE_3__,char) ; 
 int /*<<< orphan*/  RelationDropStorage (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 scalar_t__ RelationIsMapped (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationMapUpdateMap (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_4__* SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_4__*) ; 
 int /*<<< orphan*/  smgrclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_relation_set_new_filenode (TYPE_2__*,TYPE_3__*,char,scalar_t__*,scalar_t__*) ; 

void
RelationSetNewRelfilenode(Relation relation, char persistence)
{
	Oid			newrelfilenode;
	Relation	pg_class;
	HeapTuple	tuple;
	Form_pg_class classform;
	MultiXactId minmulti = InvalidMultiXactId;
	TransactionId freezeXid = InvalidTransactionId;
	RelFileNode newrnode;

	/* Allocate a new relfilenode */
	newrelfilenode = GetNewRelFileNode(relation->rd_rel->reltablespace, NULL,
									   persistence);

	/*
	 * Get a writable copy of the pg_class tuple for the given relation.
	 */
	pg_class = table_open(RelationRelationId, RowExclusiveLock);

	tuple = SearchSysCacheCopy1(RELOID,
								ObjectIdGetDatum(RelationGetRelid(relation)));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "could not find tuple for relation %u",
			 RelationGetRelid(relation));
	classform = (Form_pg_class) GETSTRUCT(tuple);

	/*
	 * Schedule unlinking of the old storage at transaction commit.
	 */
	RelationDropStorage(relation);

	/*
	 * Create storage for the main fork of the new relfilenode.  If it's a
	 * table-like object, call into the table AM to do so, which'll also
	 * create the table's init fork if needed.
	 *
	 * NOTE: If relevant for the AM, any conflict in relfilenode value will be
	 * caught here, if GetNewRelFileNode messes up for any reason.
	 */
	newrnode = relation->rd_node;
	newrnode.relNode = newrelfilenode;

	switch (relation->rd_rel->relkind)
	{
		case RELKIND_INDEX:
		case RELKIND_SEQUENCE:
			{
				/* handle these directly, at least for now */
				SMgrRelation srel;

				srel = RelationCreateStorage(newrnode, persistence);
				smgrclose(srel);
			}
			break;

		case RELKIND_RELATION:
		case RELKIND_TOASTVALUE:
		case RELKIND_MATVIEW:
			table_relation_set_new_filenode(relation, &newrnode,
											persistence,
											&freezeXid, &minmulti);
			break;

		default:
			/* we shouldn't be called for anything else */
			elog(ERROR, "relation \"%s\" does not have storage",
				 RelationGetRelationName(relation));
			break;
	}

	/*
	 * If we're dealing with a mapped index, pg_class.relfilenode doesn't
	 * change; instead we have to send the update to the relation mapper.
	 *
	 * For mapped indexes, we don't actually change the pg_class entry at all;
	 * this is essential when reindexing pg_class itself.  That leaves us with
	 * possibly-inaccurate values of relpages etc, but those will be fixed up
	 * later.
	 */
	if (RelationIsMapped(relation))
	{
		/* This case is only supported for indexes */
		Assert(relation->rd_rel->relkind == RELKIND_INDEX);

		/* Since we're not updating pg_class, these had better not change */
		Assert(classform->relfrozenxid == freezeXid);
		Assert(classform->relminmxid == minmulti);
		Assert(classform->relpersistence == persistence);

		/*
		 * In some code paths it's possible that the tuple update we'd
		 * otherwise do here is the only thing that would assign an XID for
		 * the current transaction.  However, we must have an XID to delete
		 * files, so make sure one is assigned.
		 */
		(void) GetCurrentTransactionId();

		/* Do the deed */
		RelationMapUpdateMap(RelationGetRelid(relation),
							 newrelfilenode,
							 relation->rd_rel->relisshared,
							 false);

		/* Since we're not updating pg_class, must trigger inval manually */
		CacheInvalidateRelcache(relation);
	}
	else
	{
		/* Normal case, update the pg_class entry */
		classform->relfilenode = newrelfilenode;

		/* relpages etc. never change for sequences */
		if (relation->rd_rel->relkind != RELKIND_SEQUENCE)
		{
			classform->relpages = 0;	/* it's empty until further notice */
			classform->reltuples = 0;
			classform->relallvisible = 0;
		}
		classform->relfrozenxid = freezeXid;
		classform->relminmxid = minmulti;
		classform->relpersistence = persistence;

		CatalogTupleUpdate(pg_class, &tuple->t_self, tuple);
	}

	heap_freetuple(tuple);

	table_close(pg_class, RowExclusiveLock);

	/*
	 * Make the pg_class row change or relation map change visible.  This will
	 * cause the relcache entry to get updated, too.
	 */
	CommandCounterIncrement();

	/*
	 * Mark the rel as having been given a new relfilenode in the current
	 * (sub) transaction.  This is a hint that can be used to optimize later
	 * operations on the rel in the same transaction.
	 */
	relation->rd_newRelfilenodeSubid = GetCurrentSubTransactionId();

	/* Flag relation as needing eoxact cleanup (to remove the hint) */
	EOXactListAdd(relation);
}