#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  valuesAtt ;
typedef  int /*<<< orphan*/  replacesAtt ;
typedef  int /*<<< orphan*/  nullsAtt ;
typedef  int /*<<< orphan*/  newattname ;
struct TYPE_10__ {int attisdropped; int attnotnull; char attgenerated; scalar_t__ atthasmissing; int /*<<< orphan*/  attname; scalar_t__ attstattarget; int /*<<< orphan*/  atttypid; } ;
struct TYPE_9__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  int Datum ;
typedef  int AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ATTNUM ; 
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int Anum_pg_attribute_atthasmissing ; 
 int Anum_pg_attribute_attmissingval ; 
 int /*<<< orphan*/  AttributeRelationId ; 
 int BoolGetDatum (int) ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  Int16GetDatum (int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  MemSet (int*,int,int) ; 
 int NAMEDATALEN ; 
 int Natts_pg_attribute ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveStatistics (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCacheCopy2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* heap_modify_tuple (TYPE_1__*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RemoveAttributeById(Oid relid, AttrNumber attnum)
{
	Relation	rel;
	Relation	attr_rel;
	HeapTuple	tuple;
	Form_pg_attribute attStruct;
	char		newattname[NAMEDATALEN];

	/*
	 * Grab an exclusive lock on the target table, which we will NOT release
	 * until end of transaction.  (In the simple case where we are directly
	 * dropping this column, ATExecDropColumn already did this ... but when
	 * cascading from a drop of some other object, we may not have any lock.)
	 */
	rel = relation_open(relid, AccessExclusiveLock);

	attr_rel = table_open(AttributeRelationId, RowExclusiveLock);

	tuple = SearchSysCacheCopy2(ATTNUM,
								ObjectIdGetDatum(relid),
								Int16GetDatum(attnum));
	if (!HeapTupleIsValid(tuple))	/* shouldn't happen */
		elog(ERROR, "cache lookup failed for attribute %d of relation %u",
			 attnum, relid);
	attStruct = (Form_pg_attribute) GETSTRUCT(tuple);

	if (attnum < 0)
	{
		/* System attribute (probably OID) ... just delete the row */

		CatalogTupleDelete(attr_rel, &tuple->t_self);
	}
	else
	{
		/* Dropping user attributes is lots harder */

		/* Mark the attribute as dropped */
		attStruct->attisdropped = true;

		/*
		 * Set the type OID to invalid.  A dropped attribute's type link
		 * cannot be relied on (once the attribute is dropped, the type might
		 * be too). Fortunately we do not need the type row --- the only
		 * really essential information is the type's typlen and typalign,
		 * which are preserved in the attribute's attlen and attalign.  We set
		 * atttypid to zero here as a means of catching code that incorrectly
		 * expects it to be valid.
		 */
		attStruct->atttypid = InvalidOid;

		/* Remove any NOT NULL constraint the column may have */
		attStruct->attnotnull = false;

		/* We don't want to keep stats for it anymore */
		attStruct->attstattarget = 0;

		/* Unset this so no one tries to look up the generation expression */
		attStruct->attgenerated = '\0';

		/*
		 * Change the column name to something that isn't likely to conflict
		 */
		snprintf(newattname, sizeof(newattname),
				 "........pg.dropped.%d........", attnum);
		namestrcpy(&(attStruct->attname), newattname);

		/* clear the missing value if any */
		if (attStruct->atthasmissing)
		{
			Datum		valuesAtt[Natts_pg_attribute];
			bool		nullsAtt[Natts_pg_attribute];
			bool		replacesAtt[Natts_pg_attribute];

			/* update the tuple - set atthasmissing and attmissingval */
			MemSet(valuesAtt, 0, sizeof(valuesAtt));
			MemSet(nullsAtt, false, sizeof(nullsAtt));
			MemSet(replacesAtt, false, sizeof(replacesAtt));

			valuesAtt[Anum_pg_attribute_atthasmissing - 1] =
				BoolGetDatum(false);
			replacesAtt[Anum_pg_attribute_atthasmissing - 1] = true;
			valuesAtt[Anum_pg_attribute_attmissingval - 1] = (Datum) 0;
			nullsAtt[Anum_pg_attribute_attmissingval - 1] = true;
			replacesAtt[Anum_pg_attribute_attmissingval - 1] = true;

			tuple = heap_modify_tuple(tuple, RelationGetDescr(attr_rel),
									  valuesAtt, nullsAtt, replacesAtt);
		}

		CatalogTupleUpdate(attr_rel, &tuple->t_self, tuple);
	}

	/*
	 * Because updating the pg_attribute row will trigger a relcache flush for
	 * the target relation, we need not do anything else to notify other
	 * backends of the change.
	 */

	table_close(attr_rel, RowExclusiveLock);

	if (attnum > 0)
		RemoveStatistics(relid, attnum);

	relation_close(rel, NoLock);
}