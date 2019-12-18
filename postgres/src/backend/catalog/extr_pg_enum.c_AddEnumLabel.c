#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nulls ;
typedef  int float4 ;
struct TYPE_8__ {int n_members; TYPE_1__** members; } ;
struct TYPE_7__ {int enumsortorder; int oid; int /*<<< orphan*/  enumlabel; } ;
struct TYPE_6__ {int /*<<< orphan*/  tuple; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  NameData ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__* Form_pg_enum ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_3__ CatCList ;

/* Variables and functions */
 int Anum_pg_enum_enumlabel ; 
 int Anum_pg_enum_enumsortorder ; 
 int Anum_pg_enum_enumtypid ; 
 int Anum_pg_enum_oid ; 
 int /*<<< orphan*/  CStringGetDatum (char const*) ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENUMTYPOIDNAME ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERRCODE_INVALID_NAME ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EnumOidIndexId ; 
 int /*<<< orphan*/  EnumRelationId ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 int /*<<< orphan*/  Float4GetDatum (int) ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 int GetNewOidWithIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int InvalidOid ; 
 scalar_t__ IsBinaryUpgrade ; 
 int /*<<< orphan*/  LockDatabaseObject (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NAMEDATALEN ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  NameGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int Natts_pg_enum ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int) ; 
 int /*<<< orphan*/  OidIsValid (int) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCatCacheList (TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RenumberEnumType (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/ * SearchSysCache2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* SearchSysCacheList1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TypeRelationId ; 
 int binary_upgrade_next_pg_enum_oid ; 
 int /*<<< orphan*/ * enum_blacklist ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  hash_search (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_enum_blacklist () ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ **,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort_order_cmp ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
AddEnumLabel(Oid enumTypeOid,
			 const char *newVal,
			 const char *neighbor,
			 bool newValIsAfter,
			 bool skipIfExists)
{
	Relation	pg_enum;
	Oid			newOid;
	Datum		values[Natts_pg_enum];
	bool		nulls[Natts_pg_enum];
	NameData	enumlabel;
	HeapTuple	enum_tup;
	float4		newelemorder;
	HeapTuple  *existing;
	CatCList   *list;
	int			nelems;
	int			i;

	/* check length of new label is ok */
	if (strlen(newVal) > (NAMEDATALEN - 1))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_NAME),
				 errmsg("invalid enum label \"%s\"", newVal),
				 errdetail("Labels must be %d characters or less.",
						   NAMEDATALEN - 1)));

	/*
	 * Acquire a lock on the enum type, which we won't release until commit.
	 * This ensures that two backends aren't concurrently modifying the same
	 * enum type.  Without that, we couldn't be sure to get a consistent view
	 * of the enum members via the syscache.  Note that this does not block
	 * other backends from inspecting the type; see comments for
	 * RenumberEnumType.
	 */
	LockDatabaseObject(TypeRelationId, enumTypeOid, 0, ExclusiveLock);

	/*
	 * Check if label is already in use.  The unique index on pg_enum would
	 * catch this anyway, but we prefer a friendlier error message, and
	 * besides we need a check to support IF NOT EXISTS.
	 */
	enum_tup = SearchSysCache2(ENUMTYPOIDNAME,
							   ObjectIdGetDatum(enumTypeOid),
							   CStringGetDatum(newVal));
	if (HeapTupleIsValid(enum_tup))
	{
		ReleaseSysCache(enum_tup);
		if (skipIfExists)
		{
			ereport(NOTICE,
					(errcode(ERRCODE_DUPLICATE_OBJECT),
					 errmsg("enum label \"%s\" already exists, skipping",
							newVal)));
			return;
		}
		else
			ereport(ERROR,
					(errcode(ERRCODE_DUPLICATE_OBJECT),
					 errmsg("enum label \"%s\" already exists",
							newVal)));
	}

	pg_enum = table_open(EnumRelationId, RowExclusiveLock);

	/* If we have to renumber the existing members, we restart from here */
restart:

	/* Get the list of existing members of the enum */
	list = SearchSysCacheList1(ENUMTYPOIDNAME,
							   ObjectIdGetDatum(enumTypeOid));
	nelems = list->n_members;

	/* Sort the existing members by enumsortorder */
	existing = (HeapTuple *) palloc(nelems * sizeof(HeapTuple));
	for (i = 0; i < nelems; i++)
		existing[i] = &(list->members[i]->tuple);

	qsort(existing, nelems, sizeof(HeapTuple), sort_order_cmp);

	if (neighbor == NULL)
	{
		/*
		 * Put the new label at the end of the list. No change to existing
		 * tuples is required.
		 */
		if (nelems > 0)
		{
			Form_pg_enum en = (Form_pg_enum) GETSTRUCT(existing[nelems - 1]);

			newelemorder = en->enumsortorder + 1;
		}
		else
			newelemorder = 1;
	}
	else
	{
		/* BEFORE or AFTER was specified */
		int			nbr_index;
		int			other_nbr_index;
		Form_pg_enum nbr_en;
		Form_pg_enum other_nbr_en;

		/* Locate the neighbor element */
		for (nbr_index = 0; nbr_index < nelems; nbr_index++)
		{
			Form_pg_enum en = (Form_pg_enum) GETSTRUCT(existing[nbr_index]);

			if (strcmp(NameStr(en->enumlabel), neighbor) == 0)
				break;
		}
		if (nbr_index >= nelems)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("\"%s\" is not an existing enum label",
							neighbor)));
		nbr_en = (Form_pg_enum) GETSTRUCT(existing[nbr_index]);

		/*
		 * Attempt to assign an appropriate enumsortorder value: one less than
		 * the smallest member, one more than the largest member, or halfway
		 * between two existing members.
		 *
		 * In the "halfway" case, because of the finite precision of float4,
		 * we might compute a value that's actually equal to one or the other
		 * of its neighbors.  In that case we renumber the existing members
		 * and try again.
		 */
		if (newValIsAfter)
			other_nbr_index = nbr_index + 1;
		else
			other_nbr_index = nbr_index - 1;

		if (other_nbr_index < 0)
			newelemorder = nbr_en->enumsortorder - 1;
		else if (other_nbr_index >= nelems)
			newelemorder = nbr_en->enumsortorder + 1;
		else
		{
			/*
			 * The midpoint value computed here has to be rounded to float4
			 * precision, else our equality comparisons against the adjacent
			 * values are meaningless.  The most portable way of forcing that
			 * to happen with non-C-standard-compliant compilers is to store
			 * it into a volatile variable.
			 */
			volatile float4 midpoint;

			other_nbr_en = (Form_pg_enum) GETSTRUCT(existing[other_nbr_index]);
			midpoint = (nbr_en->enumsortorder +
						other_nbr_en->enumsortorder) / 2;

			if (midpoint == nbr_en->enumsortorder ||
				midpoint == other_nbr_en->enumsortorder)
			{
				RenumberEnumType(pg_enum, existing, nelems);
				/* Clean up and start over */
				pfree(existing);
				ReleaseCatCacheList(list);
				goto restart;
			}

			newelemorder = midpoint;
		}
	}

	/* Get a new OID for the new label */
	if (IsBinaryUpgrade)
	{
		if (!OidIsValid(binary_upgrade_next_pg_enum_oid))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("pg_enum OID value not set when in binary upgrade mode")));

		/*
		 * Use binary-upgrade override for pg_enum.oid, if supplied. During
		 * binary upgrade, all pg_enum.oid's are set this way so they are
		 * guaranteed to be consistent.
		 */
		if (neighbor != NULL)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("ALTER TYPE ADD BEFORE/AFTER is incompatible with binary upgrade")));

		newOid = binary_upgrade_next_pg_enum_oid;
		binary_upgrade_next_pg_enum_oid = InvalidOid;
	}
	else
	{
		/*
		 * Normal case: we need to allocate a new Oid for the value.
		 *
		 * We want to give the new element an even-numbered Oid if it's safe,
		 * which is to say it compares correctly to all pre-existing even
		 * numbered Oids in the enum.  Otherwise, we must give it an odd Oid.
		 */
		for (;;)
		{
			bool		sorts_ok;

			/* Get a new OID (different from all existing pg_enum tuples) */
			newOid = GetNewOidWithIndex(pg_enum, EnumOidIndexId,
										Anum_pg_enum_oid);

			/*
			 * Detect whether it sorts correctly relative to existing
			 * even-numbered labels of the enum.  We can ignore existing
			 * labels with odd Oids, since a comparison involving one of those
			 * will not take the fast path anyway.
			 */
			sorts_ok = true;
			for (i = 0; i < nelems; i++)
			{
				HeapTuple	exists_tup = existing[i];
				Form_pg_enum exists_en = (Form_pg_enum) GETSTRUCT(exists_tup);
				Oid			exists_oid = exists_en->oid;

				if (exists_oid & 1)
					continue;	/* ignore odd Oids */

				if (exists_en->enumsortorder < newelemorder)
				{
					/* should sort before */
					if (exists_oid >= newOid)
					{
						sorts_ok = false;
						break;
					}
				}
				else
				{
					/* should sort after */
					if (exists_oid <= newOid)
					{
						sorts_ok = false;
						break;
					}
				}
			}

			if (sorts_ok)
			{
				/* If it's even and sorts OK, we're done. */
				if ((newOid & 1) == 0)
					break;

				/*
				 * If it's odd, and sorts OK, loop back to get another OID and
				 * try again.  Probably, the next available even OID will sort
				 * correctly too, so it's worth trying.
				 */
			}
			else
			{
				/*
				 * If it's odd, and does not sort correctly, we're done.
				 * (Probably, the next available even OID would sort
				 * incorrectly too, so no point in trying again.)
				 */
				if (newOid & 1)
					break;

				/*
				 * If it's even, and does not sort correctly, loop back to get
				 * another OID and try again.  (We *must* reject this case.)
				 */
			}
		}
	}

	/* Done with info about existing members */
	pfree(existing);
	ReleaseCatCacheList(list);

	/* Create the new pg_enum entry */
	memset(nulls, false, sizeof(nulls));
	values[Anum_pg_enum_oid - 1] = ObjectIdGetDatum(newOid);
	values[Anum_pg_enum_enumtypid - 1] = ObjectIdGetDatum(enumTypeOid);
	values[Anum_pg_enum_enumsortorder - 1] = Float4GetDatum(newelemorder);
	namestrcpy(&enumlabel, newVal);
	values[Anum_pg_enum_enumlabel - 1] = NameGetDatum(&enumlabel);
	enum_tup = heap_form_tuple(RelationGetDescr(pg_enum), values, nulls);
	CatalogTupleInsert(pg_enum, enum_tup);
	heap_freetuple(enum_tup);

	table_close(pg_enum, RowExclusiveLock);

	/* Set up the blacklist hash if not already done in this transaction */
	if (enum_blacklist == NULL)
		init_enum_blacklist();

	/* Add the new value to the blacklist */
	(void) hash_search(enum_blacklist, &newOid, HASH_ENTER, NULL);
}