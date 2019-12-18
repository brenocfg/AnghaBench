#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ attisdropped; } ;
struct TYPE_3__ {scalar_t__ relkind; int relnatts; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_class ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ATTNUM ; 
 scalar_t__ AccessMethodRelationId ; 
 scalar_t__ AggregateRelationId ; 
 int /*<<< orphan*/  Anum_pg_attribute_attacl ; 
 int /*<<< orphan*/  Anum_pg_class_relacl ; 
 int /*<<< orphan*/  Anum_pg_foreign_data_wrapper_fdwacl ; 
 int /*<<< orphan*/  Anum_pg_foreign_server_srvacl ; 
 int /*<<< orphan*/  Anum_pg_language_lanacl ; 
 int /*<<< orphan*/  Anum_pg_largeobject_metadata_lomacl ; 
 int /*<<< orphan*/  Anum_pg_largeobject_metadata_oid ; 
 int /*<<< orphan*/  Anum_pg_namespace_nspacl ; 
 int /*<<< orphan*/  Anum_pg_proc_proacl ; 
 int /*<<< orphan*/  Anum_pg_type_typacl ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 scalar_t__ CastRelationId ; 
 scalar_t__ CollationRelationId ; 
 scalar_t__ ConversionRelationId ; 
 int /*<<< orphan*/  DatumGetAclP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ EventTriggerRelationId ; 
 int /*<<< orphan*/  FOREIGNDATAWRAPPEROID ; 
 int /*<<< orphan*/  FOREIGNSERVEROID ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ ForeignDataWrapperRelationId ; 
 scalar_t__ ForeignServerRelationId ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int16GetDatum (int) ; 
 int /*<<< orphan*/  LANGOID ; 
 scalar_t__ LanguageRelationId ; 
 int /*<<< orphan*/  LargeObjectMetadataOidIndexId ; 
 scalar_t__ LargeObjectMetadataRelationId ; 
 int /*<<< orphan*/  NAMESPACEOID ; 
 scalar_t__ NamespaceRelationId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 scalar_t__ OperatorClassRelationId ; 
 scalar_t__ OperatorFamilyRelationId ; 
 scalar_t__ OperatorRelationId ; 
 int /*<<< orphan*/  PROCOID ; 
 scalar_t__ ProcedureRelationId ; 
 scalar_t__ RELKIND_COMPOSITE_TYPE ; 
 scalar_t__ RELKIND_INDEX ; 
 scalar_t__ RELKIND_PARTITIONED_INDEX ; 
 scalar_t__ RELKIND_SEQUENCE ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationRelationId ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ TSConfigRelationId ; 
 scalar_t__ TSDictionaryRelationId ; 
 scalar_t__ TSParserRelationId ; 
 scalar_t__ TSTemplateRelationId ; 
 int /*<<< orphan*/  TYPEOID ; 
 scalar_t__ TransformRelationId ; 
 scalar_t__ TypeRelationId ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  recordExtensionInitPrivWorker (scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (scalar_t__,int /*<<< orphan*/ ) ; 

void
recordExtObjInitPriv(Oid objoid, Oid classoid)
{
	/*
	 * pg_class / pg_attribute
	 *
	 * If this is a relation then we need to see if there are any sub-objects
	 * (eg: columns) for it and, if so, be sure to call
	 * recordExtensionInitPrivWorker() for each one.
	 */
	if (classoid == RelationRelationId)
	{
		Form_pg_class pg_class_tuple;
		Datum		aclDatum;
		bool		isNull;
		HeapTuple	tuple;

		tuple = SearchSysCache1(RELOID, ObjectIdGetDatum(objoid));
		if (!HeapTupleIsValid(tuple))
			elog(ERROR, "cache lookup failed for relation %u", objoid);
		pg_class_tuple = (Form_pg_class) GETSTRUCT(tuple);

		/* Indexes don't have permissions */
		if (pg_class_tuple->relkind == RELKIND_INDEX ||
			pg_class_tuple->relkind == RELKIND_PARTITIONED_INDEX)
			return;

		/* Composite types don't have permissions either */
		if (pg_class_tuple->relkind == RELKIND_COMPOSITE_TYPE)
			return;

		/*
		 * If this isn't a sequence, index, or composite type then it's
		 * possibly going to have columns associated with it that might have
		 * ACLs.
		 */
		if (pg_class_tuple->relkind != RELKIND_SEQUENCE)
		{
			AttrNumber	curr_att;
			AttrNumber	nattrs = pg_class_tuple->relnatts;

			for (curr_att = 1; curr_att <= nattrs; curr_att++)
			{
				HeapTuple	attTuple;
				Datum		attaclDatum;

				attTuple = SearchSysCache2(ATTNUM,
										   ObjectIdGetDatum(objoid),
										   Int16GetDatum(curr_att));

				if (!HeapTupleIsValid(attTuple))
					continue;

				/* ignore dropped columns */
				if (((Form_pg_attribute) GETSTRUCT(attTuple))->attisdropped)
				{
					ReleaseSysCache(attTuple);
					continue;
				}

				attaclDatum = SysCacheGetAttr(ATTNUM, attTuple,
											  Anum_pg_attribute_attacl,
											  &isNull);

				/* no need to do anything for a NULL ACL */
				if (isNull)
				{
					ReleaseSysCache(attTuple);
					continue;
				}

				recordExtensionInitPrivWorker(objoid, classoid, curr_att,
											  DatumGetAclP(attaclDatum));

				ReleaseSysCache(attTuple);
			}
		}

		aclDatum = SysCacheGetAttr(RELOID, tuple, Anum_pg_class_relacl,
								   &isNull);

		/* Add the record, if any, for the top-level object */
		if (!isNull)
			recordExtensionInitPrivWorker(objoid, classoid, 0,
										  DatumGetAclP(aclDatum));

		ReleaseSysCache(tuple);
	}
	/* pg_foreign_data_wrapper */
	else if (classoid == ForeignDataWrapperRelationId)
	{
		Datum		aclDatum;
		bool		isNull;
		HeapTuple	tuple;

		tuple = SearchSysCache1(FOREIGNDATAWRAPPEROID,
								ObjectIdGetDatum(objoid));
		if (!HeapTupleIsValid(tuple))
			elog(ERROR, "cache lookup failed for foreign data wrapper %u",
				 objoid);

		aclDatum = SysCacheGetAttr(FOREIGNDATAWRAPPEROID, tuple,
								   Anum_pg_foreign_data_wrapper_fdwacl,
								   &isNull);

		/* Add the record, if any, for the top-level object */
		if (!isNull)
			recordExtensionInitPrivWorker(objoid, classoid, 0,
										  DatumGetAclP(aclDatum));

		ReleaseSysCache(tuple);
	}
	/* pg_foreign_server */
	else if (classoid == ForeignServerRelationId)
	{
		Datum		aclDatum;
		bool		isNull;
		HeapTuple	tuple;

		tuple = SearchSysCache1(FOREIGNSERVEROID, ObjectIdGetDatum(objoid));
		if (!HeapTupleIsValid(tuple))
			elog(ERROR, "cache lookup failed for foreign data wrapper %u",
				 objoid);

		aclDatum = SysCacheGetAttr(FOREIGNSERVEROID, tuple,
								   Anum_pg_foreign_server_srvacl,
								   &isNull);

		/* Add the record, if any, for the top-level object */
		if (!isNull)
			recordExtensionInitPrivWorker(objoid, classoid, 0,
										  DatumGetAclP(aclDatum));

		ReleaseSysCache(tuple);
	}
	/* pg_language */
	else if (classoid == LanguageRelationId)
	{
		Datum		aclDatum;
		bool		isNull;
		HeapTuple	tuple;

		tuple = SearchSysCache1(LANGOID, ObjectIdGetDatum(objoid));
		if (!HeapTupleIsValid(tuple))
			elog(ERROR, "cache lookup failed for language %u", objoid);

		aclDatum = SysCacheGetAttr(LANGOID, tuple, Anum_pg_language_lanacl,
								   &isNull);

		/* Add the record, if any, for the top-level object */
		if (!isNull)
			recordExtensionInitPrivWorker(objoid, classoid, 0,
										  DatumGetAclP(aclDatum));

		ReleaseSysCache(tuple);
	}
	/* pg_largeobject_metadata */
	else if (classoid == LargeObjectMetadataRelationId)
	{
		Datum		aclDatum;
		bool		isNull;
		HeapTuple	tuple;
		ScanKeyData entry[1];
		SysScanDesc scan;
		Relation	relation;

		relation = table_open(LargeObjectMetadataRelationId, RowExclusiveLock);

		/* There's no syscache for pg_largeobject_metadata */
		ScanKeyInit(&entry[0],
					Anum_pg_largeobject_metadata_oid,
					BTEqualStrategyNumber, F_OIDEQ,
					ObjectIdGetDatum(objoid));

		scan = systable_beginscan(relation,
								  LargeObjectMetadataOidIndexId, true,
								  NULL, 1, entry);

		tuple = systable_getnext(scan);
		if (!HeapTupleIsValid(tuple))
			elog(ERROR, "could not find tuple for large object %u", objoid);

		aclDatum = heap_getattr(tuple,
								Anum_pg_largeobject_metadata_lomacl,
								RelationGetDescr(relation), &isNull);

		/* Add the record, if any, for the top-level object */
		if (!isNull)
			recordExtensionInitPrivWorker(objoid, classoid, 0,
										  DatumGetAclP(aclDatum));

		systable_endscan(scan);
	}
	/* pg_namespace */
	else if (classoid == NamespaceRelationId)
	{
		Datum		aclDatum;
		bool		isNull;
		HeapTuple	tuple;

		tuple = SearchSysCache1(NAMESPACEOID, ObjectIdGetDatum(objoid));
		if (!HeapTupleIsValid(tuple))
			elog(ERROR, "cache lookup failed for function %u", objoid);

		aclDatum = SysCacheGetAttr(NAMESPACEOID, tuple,
								   Anum_pg_namespace_nspacl, &isNull);

		/* Add the record, if any, for the top-level object */
		if (!isNull)
			recordExtensionInitPrivWorker(objoid, classoid, 0,
										  DatumGetAclP(aclDatum));

		ReleaseSysCache(tuple);
	}
	/* pg_proc */
	else if (classoid == ProcedureRelationId)
	{
		Datum		aclDatum;
		bool		isNull;
		HeapTuple	tuple;

		tuple = SearchSysCache1(PROCOID, ObjectIdGetDatum(objoid));
		if (!HeapTupleIsValid(tuple))
			elog(ERROR, "cache lookup failed for function %u", objoid);

		aclDatum = SysCacheGetAttr(PROCOID, tuple, Anum_pg_proc_proacl,
								   &isNull);

		/* Add the record, if any, for the top-level object */
		if (!isNull)
			recordExtensionInitPrivWorker(objoid, classoid, 0,
										  DatumGetAclP(aclDatum));

		ReleaseSysCache(tuple);
	}
	/* pg_type */
	else if (classoid == TypeRelationId)
	{
		Datum		aclDatum;
		bool		isNull;
		HeapTuple	tuple;

		tuple = SearchSysCache1(TYPEOID, ObjectIdGetDatum(objoid));
		if (!HeapTupleIsValid(tuple))
			elog(ERROR, "cache lookup failed for function %u", objoid);

		aclDatum = SysCacheGetAttr(TYPEOID, tuple, Anum_pg_type_typacl,
								   &isNull);

		/* Add the record, if any, for the top-level object */
		if (!isNull)
			recordExtensionInitPrivWorker(objoid, classoid, 0,
										  DatumGetAclP(aclDatum));

		ReleaseSysCache(tuple);
	}
	else if (classoid == AccessMethodRelationId ||
			 classoid == AggregateRelationId ||
			 classoid == CastRelationId ||
			 classoid == CollationRelationId ||
			 classoid == ConversionRelationId ||
			 classoid == EventTriggerRelationId ||
			 classoid == OperatorRelationId ||
			 classoid == OperatorClassRelationId ||
			 classoid == OperatorFamilyRelationId ||
			 classoid == NamespaceRelationId ||
			 classoid == TSConfigRelationId ||
			 classoid == TSDictionaryRelationId ||
			 classoid == TSParserRelationId ||
			 classoid == TSTemplateRelationId ||
			 classoid == TransformRelationId
		)
	{
		/* no ACL for these object types, so do nothing. */
	}

	/*
	 * complain if we are given a class OID for a class that extensions don't
	 * support or that we don't recognize.
	 */
	else
	{
		elog(ERROR, "unrecognized or unsupported class OID: %u", classoid);
	}
}