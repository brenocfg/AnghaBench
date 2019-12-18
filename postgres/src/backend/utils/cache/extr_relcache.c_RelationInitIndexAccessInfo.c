#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16 ;
struct TYPE_17__ {int /*<<< orphan*/  values; } ;
typedef  TYPE_3__ oidvector ;
struct TYPE_18__ {int /*<<< orphan*/  values; } ;
typedef  TYPE_4__ int2vector ;
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_20__ {int /*<<< orphan*/  amhandler; } ;
struct TYPE_19__ {int /*<<< orphan*/ * rd_amcache; int /*<<< orphan*/ * rd_exclstrats; int /*<<< orphan*/ * rd_exclprocs; int /*<<< orphan*/ * rd_exclops; void* rd_indpred; void* rd_indexprs; int /*<<< orphan*/ * rd_indoption; int /*<<< orphan*/  rd_indextuple; int /*<<< orphan*/ * rd_opcintype; int /*<<< orphan*/ * rd_opfamily; int /*<<< orphan*/ * rd_support; int /*<<< orphan*/ * rd_indcollation; int /*<<< orphan*/ * rd_supportinfo; TYPE_2__* rd_indam; int /*<<< orphan*/  rd_indexcxt; int /*<<< orphan*/  rd_amhandler; TYPE_1__* rd_rel; scalar_t__ rd_index; } ;
struct TYPE_16__ {int amsupport; } ;
struct TYPE_15__ {int /*<<< orphan*/  relam; } ;
typedef  TYPE_5__* Relation ;
typedef  int /*<<< orphan*/  RegProcedure ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  scalar_t__ Form_pg_index ;
typedef  TYPE_6__* Form_pg_am ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_SMALL_SIZES ; 
 int /*<<< orphan*/  AMOID ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Anum_pg_index_indclass ; 
 int /*<<< orphan*/  Anum_pg_index_indcollation ; 
 int /*<<< orphan*/  Anum_pg_index_indoption ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetPgIndexDescriptor () ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDEXRELID ; 
 int IndexRelationGetNumberOfAttributes (TYPE_5__*) ; 
 int IndexRelationGetNumberOfKeyAttributes (TYPE_5__*) ; 
 int /*<<< orphan*/  IndexSupportInitialize (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  InitIndexAmRoutine (TYPE_5__*) ; 
 scalar_t__ MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextCopyAndSetIdentifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 void* NIL ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int RelationGetNumberOfAttributes (TYPE_5__*) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_5__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_5__*) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fastgetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  heap_copytuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
RelationInitIndexAccessInfo(Relation relation)
{
	HeapTuple	tuple;
	Form_pg_am	aform;
	Datum		indcollDatum;
	Datum		indclassDatum;
	Datum		indoptionDatum;
	bool		isnull;
	oidvector  *indcoll;
	oidvector  *indclass;
	int2vector *indoption;
	MemoryContext indexcxt;
	MemoryContext oldcontext;
	int			indnatts;
	int			indnkeyatts;
	uint16		amsupport;

	/*
	 * Make a copy of the pg_index entry for the index.  Since pg_index
	 * contains variable-length and possibly-null fields, we have to do this
	 * honestly rather than just treating it as a Form_pg_index struct.
	 */
	tuple = SearchSysCache1(INDEXRELID,
							ObjectIdGetDatum(RelationGetRelid(relation)));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for index %u",
			 RelationGetRelid(relation));
	oldcontext = MemoryContextSwitchTo(CacheMemoryContext);
	relation->rd_indextuple = heap_copytuple(tuple);
	relation->rd_index = (Form_pg_index) GETSTRUCT(relation->rd_indextuple);
	MemoryContextSwitchTo(oldcontext);
	ReleaseSysCache(tuple);

	/*
	 * Look up the index's access method, save the OID of its handler function
	 */
	tuple = SearchSysCache1(AMOID, ObjectIdGetDatum(relation->rd_rel->relam));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for access method %u",
			 relation->rd_rel->relam);
	aform = (Form_pg_am) GETSTRUCT(tuple);
	relation->rd_amhandler = aform->amhandler;
	ReleaseSysCache(tuple);

	indnatts = RelationGetNumberOfAttributes(relation);
	if (indnatts != IndexRelationGetNumberOfAttributes(relation))
		elog(ERROR, "relnatts disagrees with indnatts for index %u",
			 RelationGetRelid(relation));
	indnkeyatts = IndexRelationGetNumberOfKeyAttributes(relation);

	/*
	 * Make the private context to hold index access info.  The reason we need
	 * a context, and not just a couple of pallocs, is so that we won't leak
	 * any subsidiary info attached to fmgr lookup records.
	 */
	indexcxt = AllocSetContextCreate(CacheMemoryContext,
									 "index info",
									 ALLOCSET_SMALL_SIZES);
	relation->rd_indexcxt = indexcxt;
	MemoryContextCopyAndSetIdentifier(indexcxt,
									  RelationGetRelationName(relation));

	/*
	 * Now we can fetch the index AM's API struct
	 */
	InitIndexAmRoutine(relation);

	/*
	 * Allocate arrays to hold data. Opclasses are not used for included
	 * columns, so allocate them for indnkeyatts only.
	 */
	relation->rd_opfamily = (Oid *)
		MemoryContextAllocZero(indexcxt, indnkeyatts * sizeof(Oid));
	relation->rd_opcintype = (Oid *)
		MemoryContextAllocZero(indexcxt, indnkeyatts * sizeof(Oid));

	amsupport = relation->rd_indam->amsupport;
	if (amsupport > 0)
	{
		int			nsupport = indnatts * amsupport;

		relation->rd_support = (RegProcedure *)
			MemoryContextAllocZero(indexcxt, nsupport * sizeof(RegProcedure));
		relation->rd_supportinfo = (FmgrInfo *)
			MemoryContextAllocZero(indexcxt, nsupport * sizeof(FmgrInfo));
	}
	else
	{
		relation->rd_support = NULL;
		relation->rd_supportinfo = NULL;
	}

	relation->rd_indcollation = (Oid *)
		MemoryContextAllocZero(indexcxt, indnkeyatts * sizeof(Oid));

	relation->rd_indoption = (int16 *)
		MemoryContextAllocZero(indexcxt, indnkeyatts * sizeof(int16));

	/*
	 * indcollation cannot be referenced directly through the C struct,
	 * because it comes after the variable-width indkey field.  Must extract
	 * the datum the hard way...
	 */
	indcollDatum = fastgetattr(relation->rd_indextuple,
							   Anum_pg_index_indcollation,
							   GetPgIndexDescriptor(),
							   &isnull);
	Assert(!isnull);
	indcoll = (oidvector *) DatumGetPointer(indcollDatum);
	memcpy(relation->rd_indcollation, indcoll->values, indnkeyatts * sizeof(Oid));

	/*
	 * indclass cannot be referenced directly through the C struct, because it
	 * comes after the variable-width indkey field.  Must extract the datum
	 * the hard way...
	 */
	indclassDatum = fastgetattr(relation->rd_indextuple,
								Anum_pg_index_indclass,
								GetPgIndexDescriptor(),
								&isnull);
	Assert(!isnull);
	indclass = (oidvector *) DatumGetPointer(indclassDatum);

	/*
	 * Fill the support procedure OID array, as well as the info about
	 * opfamilies and opclass input types.  (aminfo and supportinfo are left
	 * as zeroes, and are filled on-the-fly when used)
	 */
	IndexSupportInitialize(indclass, relation->rd_support,
						   relation->rd_opfamily, relation->rd_opcintype,
						   amsupport, indnkeyatts);

	/*
	 * Similarly extract indoption and copy it to the cache entry
	 */
	indoptionDatum = fastgetattr(relation->rd_indextuple,
								 Anum_pg_index_indoption,
								 GetPgIndexDescriptor(),
								 &isnull);
	Assert(!isnull);
	indoption = (int2vector *) DatumGetPointer(indoptionDatum);
	memcpy(relation->rd_indoption, indoption->values, indnkeyatts * sizeof(int16));

	/*
	 * expressions, predicate, exclusion caches will be filled later
	 */
	relation->rd_indexprs = NIL;
	relation->rd_indpred = NIL;
	relation->rd_exclops = NULL;
	relation->rd_exclprocs = NULL;
	relation->rd_exclstrats = NULL;
	relation->rd_amcache = NULL;
}