#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_12__ {scalar_t__ objectSubId; void* objectId; int /*<<< orphan*/  classId; } ;
struct TYPE_11__ {int /*<<< orphan*/  rd_att; } ;
typedef  TYPE_1__* Relation ;
typedef  void* Oid ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/  NameData ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int Anum_pg_conversion_condefault ; 
 int Anum_pg_conversion_conforencoding ; 
 int Anum_pg_conversion_conname ; 
 int Anum_pg_conversion_connamespace ; 
 int Anum_pg_conversion_conowner ; 
 int Anum_pg_conversion_conproc ; 
 int Anum_pg_conversion_contoencoding ; 
 int Anum_pg_conversion_oid ; 
 scalar_t__ BoolGetDatum (int) ; 
 int /*<<< orphan*/  CONNAMENSP ; 
 int /*<<< orphan*/  CatalogTupleInsert (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConversionOidIndexId ; 
 int /*<<< orphan*/  ConversionRelationId ; 
 int /*<<< orphan*/  DEPENDENCY_NORMAL ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FindDefaultConversion (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* GetNewOidWithIndex (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvokeObjectPostCreateHook (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ NameGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NamespaceRelationId ; 
 int Natts_pg_conversion ; 
 scalar_t__ ObjectIdGetDatum (void*) ; 
 int /*<<< orphan*/  PointerGetDatum (char const*) ; 
 int /*<<< orphan*/  ProcedureRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 scalar_t__ SearchSysCacheExists2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,...) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pg_encoding_to_char (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordDependencyOnCurrentExtension (TYPE_2__*,int) ; 
 int /*<<< orphan*/  recordDependencyOnOwner (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  table_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ObjectAddress
ConversionCreate(const char *conname, Oid connamespace,
				 Oid conowner,
				 int32 conforencoding, int32 contoencoding,
				 Oid conproc, bool def)
{
	int			i;
	Relation	rel;
	TupleDesc	tupDesc;
	HeapTuple	tup;
	Oid			oid;
	bool		nulls[Natts_pg_conversion];
	Datum		values[Natts_pg_conversion];
	NameData	cname;
	ObjectAddress myself,
				referenced;

	/* sanity checks */
	if (!conname)
		elog(ERROR, "no conversion name supplied");

	/* make sure there is no existing conversion of same name */
	if (SearchSysCacheExists2(CONNAMENSP,
							  PointerGetDatum(conname),
							  ObjectIdGetDatum(connamespace)))
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("conversion \"%s\" already exists", conname)));

	if (def)
	{
		/*
		 * make sure there is no existing default <for encoding><to encoding>
		 * pair in this name space
		 */
		if (FindDefaultConversion(connamespace,
								  conforencoding,
								  contoencoding))
			ereport(ERROR,
					(errcode(ERRCODE_DUPLICATE_OBJECT),
					 errmsg("default conversion for %s to %s already exists",
							pg_encoding_to_char(conforencoding),
							pg_encoding_to_char(contoencoding))));
	}

	/* open pg_conversion */
	rel = table_open(ConversionRelationId, RowExclusiveLock);
	tupDesc = rel->rd_att;

	/* initialize nulls and values */
	for (i = 0; i < Natts_pg_conversion; i++)
	{
		nulls[i] = false;
		values[i] = (Datum) NULL;
	}

	/* form a tuple */
	namestrcpy(&cname, conname);
	oid = GetNewOidWithIndex(rel, ConversionOidIndexId,
							 Anum_pg_conversion_oid);
	values[Anum_pg_conversion_oid - 1] = ObjectIdGetDatum(oid);
	values[Anum_pg_conversion_conname - 1] = NameGetDatum(&cname);
	values[Anum_pg_conversion_connamespace - 1] = ObjectIdGetDatum(connamespace);
	values[Anum_pg_conversion_conowner - 1] = ObjectIdGetDatum(conowner);
	values[Anum_pg_conversion_conforencoding - 1] = Int32GetDatum(conforencoding);
	values[Anum_pg_conversion_contoencoding - 1] = Int32GetDatum(contoencoding);
	values[Anum_pg_conversion_conproc - 1] = ObjectIdGetDatum(conproc);
	values[Anum_pg_conversion_condefault - 1] = BoolGetDatum(def);

	tup = heap_form_tuple(tupDesc, values, nulls);

	/* insert a new tuple */
	CatalogTupleInsert(rel, tup);

	myself.classId = ConversionRelationId;
	myself.objectId = oid;
	myself.objectSubId = 0;

	/* create dependency on conversion procedure */
	referenced.classId = ProcedureRelationId;
	referenced.objectId = conproc;
	referenced.objectSubId = 0;
	recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);

	/* create dependency on namespace */
	referenced.classId = NamespaceRelationId;
	referenced.objectId = connamespace;
	referenced.objectSubId = 0;
	recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);

	/* create dependency on owner */
	recordDependencyOnOwner(ConversionRelationId, oid, conowner);

	/* dependency on extension */
	recordDependencyOnCurrentExtension(&myself, false);

	/* Post creation hook for new conversion */
	InvokeObjectPostCreateHook(ConversionRelationId, oid, 0);

	heap_freetuple(tup);
	table_close(rel, RowExclusiveLock);

	return myself;
}