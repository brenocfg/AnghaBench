#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ oprcom; scalar_t__ oprnegate; } ;
struct TYPE_7__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_operator ;

/* Variables and functions */
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  GETSTRUCT (TYPE_1__*) ; 
 scalar_t__ HeapTupleIsValid (TYPE_1__*) ; 
 void* InvalidOid ; 
 int /*<<< orphan*/  OPEROID ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  OperatorRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
OperatorUpd(Oid baseId, Oid commId, Oid negId, bool isDelete)
{
	Relation	pg_operator_desc;
	HeapTuple	tup;

	/*
	 * If we're making an operator into its own commutator, then we need a
	 * command-counter increment here, since we've just inserted the tuple
	 * we're about to update.  But when we're dropping an operator, we can
	 * skip this because we're at the beginning of the command.
	 */
	if (!isDelete)
		CommandCounterIncrement();

	/* Open the relation. */
	pg_operator_desc = table_open(OperatorRelationId, RowExclusiveLock);

	/* Get a writable copy of the commutator's tuple. */
	if (OidIsValid(commId))
		tup = SearchSysCacheCopy1(OPEROID, ObjectIdGetDatum(commId));
	else
		tup = NULL;

	/* Update the commutator's tuple if need be. */
	if (HeapTupleIsValid(tup))
	{
		Form_pg_operator t = (Form_pg_operator) GETSTRUCT(tup);
		bool		update_commutator = false;

		/*
		 * Out of due caution, we only change the commutator's oprcom field if
		 * it has the exact value we expected: InvalidOid when creating an
		 * operator, or baseId when dropping one.
		 */
		if (isDelete && t->oprcom == baseId)
		{
			t->oprcom = InvalidOid;
			update_commutator = true;
		}
		else if (!isDelete && !OidIsValid(t->oprcom))
		{
			t->oprcom = baseId;
			update_commutator = true;
		}

		/* If any columns were found to need modification, update tuple. */
		if (update_commutator)
		{
			CatalogTupleUpdate(pg_operator_desc, &tup->t_self, tup);

			/*
			 * Do CCI to make the updated tuple visible.  We must do this in
			 * case the commutator is also the negator.  (Which would be a
			 * logic error on the operator definer's part, but that's not a
			 * good reason to fail here.)  We would need a CCI anyway in the
			 * deletion case for a self-commutator with no negator.
			 */
			CommandCounterIncrement();
		}
	}

	/*
	 * Similarly find and update the negator, if any.
	 */
	if (OidIsValid(negId))
		tup = SearchSysCacheCopy1(OPEROID, ObjectIdGetDatum(negId));
	else
		tup = NULL;

	if (HeapTupleIsValid(tup))
	{
		Form_pg_operator t = (Form_pg_operator) GETSTRUCT(tup);
		bool		update_negator = false;

		/*
		 * Out of due caution, we only change the negator's oprnegate field if
		 * it has the exact value we expected: InvalidOid when creating an
		 * operator, or baseId when dropping one.
		 */
		if (isDelete && t->oprnegate == baseId)
		{
			t->oprnegate = InvalidOid;
			update_negator = true;
		}
		else if (!isDelete && !OidIsValid(t->oprnegate))
		{
			t->oprnegate = baseId;
			update_negator = true;
		}

		/* If any columns were found to need modification, update tuple. */
		if (update_negator)
		{
			CatalogTupleUpdate(pg_operator_desc, &tup->t_self, tup);

			/*
			 * In the deletion case, do CCI to make the updated tuple visible.
			 * We must do this in case the operator is its own negator. (Which
			 * would be a logic error on the operator definer's part, but
			 * that's not a good reason to fail here.)
			 */
			if (isDelete)
				CommandCounterIncrement();
		}
	}

	/* Close relation and release catalog lock. */
	table_close(pg_operator_desc, RowExclusiveLock);
}