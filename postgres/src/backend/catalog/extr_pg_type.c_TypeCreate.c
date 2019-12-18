#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
typedef  int int16 ;
struct TYPE_13__ {scalar_t__ typowner; scalar_t__ oid; scalar_t__ typisdefined; } ;
struct TYPE_12__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  NameData ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_type ;
typedef  scalar_t__ Datum ;
typedef  int /*<<< orphan*/  Acl ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 int Anum_pg_type_oid ; 
 int Anum_pg_type_typacl ; 
 int Anum_pg_type_typalign ; 
 int Anum_pg_type_typanalyze ; 
 int Anum_pg_type_typarray ; 
 int Anum_pg_type_typbasetype ; 
 int Anum_pg_type_typbyval ; 
 int Anum_pg_type_typcategory ; 
 int Anum_pg_type_typcollation ; 
 int Anum_pg_type_typdefault ; 
 int Anum_pg_type_typdefaultbin ; 
 int Anum_pg_type_typdelim ; 
 int Anum_pg_type_typelem ; 
 int Anum_pg_type_typinput ; 
 int Anum_pg_type_typisdefined ; 
 int Anum_pg_type_typispreferred ; 
 int Anum_pg_type_typlen ; 
 int Anum_pg_type_typmodin ; 
 int Anum_pg_type_typmodout ; 
 int Anum_pg_type_typname ; 
 int Anum_pg_type_typnamespace ; 
 int Anum_pg_type_typndims ; 
 int Anum_pg_type_typnotnull ; 
 int Anum_pg_type_typoutput ; 
 int Anum_pg_type_typowner ; 
 int Anum_pg_type_typreceive ; 
 int Anum_pg_type_typrelid ; 
 int Anum_pg_type_typsend ; 
 int Anum_pg_type_typstorage ; 
 int Anum_pg_type_typtype ; 
 int Anum_pg_type_typtypmod ; 
 scalar_t__ BoolGetDatum (int) ; 
 int /*<<< orphan*/  CStringGetDatum (char const*) ; 
 scalar_t__ CStringGetTextDatum (char const*) ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ CharGetDatum (char) ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERRCODE_INVALID_OBJECT_DEFINITION ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  GenerateTypeDependencies (scalar_t__,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char,int,int,int) ; 
 scalar_t__ GetNewOidWithIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ HeapTupleIsValid (TYPE_1__*) ; 
 scalar_t__ Int16GetDatum (int) ; 
 scalar_t__ Int32GetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  InvokeObjectPostCreateHook (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ IsBinaryUpgrade ; 
 int /*<<< orphan*/  IsBootstrapProcessingMode () ; 
 scalar_t__ NameGetDatum (int /*<<< orphan*/ *) ; 
 int Natts_pg_type ; 
 int /*<<< orphan*/  OBJECT_TYPE ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ObjectIdGetDatum (scalar_t__) ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 scalar_t__ PointerGetDatum (int /*<<< orphan*/ *) ; 
 char RELKIND_COMPOSITE_TYPE ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCacheCopy2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TYPENAMENSP ; 
 int /*<<< orphan*/  TypeOidIndexId ; 
 int /*<<< orphan*/  TypeRelationId ; 
 int /*<<< orphan*/  aclcheck_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ binary_upgrade_next_pg_type_oid ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/ * get_user_default_acl (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 TYPE_1__* heap_form_tuple (int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 TYPE_1__* heap_modify_tuple (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*,int*,int*) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * stringToNode (char*) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ObjectAddress
TypeCreate(Oid newTypeOid,
		   const char *typeName,
		   Oid typeNamespace,
		   Oid relationOid,		/* only for relation rowtypes */
		   char relationKind,	/* ditto */
		   Oid ownerId,
		   int16 internalSize,
		   char typeType,
		   char typeCategory,
		   bool typePreferred,
		   char typDelim,
		   Oid inputProcedure,
		   Oid outputProcedure,
		   Oid receiveProcedure,
		   Oid sendProcedure,
		   Oid typmodinProcedure,
		   Oid typmodoutProcedure,
		   Oid analyzeProcedure,
		   Oid elementType,
		   bool isImplicitArray,
		   Oid arrayType,
		   Oid baseType,
		   const char *defaultTypeValue,	/* human readable rep */
		   char *defaultTypeBin,	/* cooked rep */
		   bool passedByValue,
		   char alignment,
		   char storage,
		   int32 typeMod,
		   int32 typNDims,		/* Array dimensions for baseType */
		   bool typeNotNull,
		   Oid typeCollation)
{
	Relation	pg_type_desc;
	Oid			typeObjectId;
	bool		isDependentType;
	bool		rebuildDeps = false;
	Acl		   *typacl;
	HeapTuple	tup;
	bool		nulls[Natts_pg_type];
	bool		replaces[Natts_pg_type];
	Datum		values[Natts_pg_type];
	NameData	name;
	int			i;
	ObjectAddress address;

	/*
	 * We assume that the caller validated the arguments individually, but did
	 * not check for bad combinations.
	 *
	 * Validate size specifications: either positive (fixed-length) or -1
	 * (varlena) or -2 (cstring).
	 */
	if (!(internalSize > 0 ||
		  internalSize == -1 ||
		  internalSize == -2))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
				 errmsg("invalid type internal size %d",
						internalSize)));

	if (passedByValue)
	{
		/*
		 * Pass-by-value types must have a fixed length that is one of the
		 * values supported by fetch_att() and store_att_byval(); and the
		 * alignment had better agree, too.  All this code must match
		 * access/tupmacs.h!
		 */
		if (internalSize == (int16) sizeof(char))
		{
			if (alignment != 'c')
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
						 errmsg("alignment \"%c\" is invalid for passed-by-value type of size %d",
								alignment, internalSize)));
		}
		else if (internalSize == (int16) sizeof(int16))
		{
			if (alignment != 's')
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
						 errmsg("alignment \"%c\" is invalid for passed-by-value type of size %d",
								alignment, internalSize)));
		}
		else if (internalSize == (int16) sizeof(int32))
		{
			if (alignment != 'i')
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
						 errmsg("alignment \"%c\" is invalid for passed-by-value type of size %d",
								alignment, internalSize)));
		}
#if SIZEOF_DATUM == 8
		else if (internalSize == (int16) sizeof(Datum))
		{
			if (alignment != 'd')
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
						 errmsg("alignment \"%c\" is invalid for passed-by-value type of size %d",
								alignment, internalSize)));
		}
#endif
		else
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
					 errmsg("internal size %d is invalid for passed-by-value type",
							internalSize)));
	}
	else
	{
		/* varlena types must have int align or better */
		if (internalSize == -1 && !(alignment == 'i' || alignment == 'd'))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
					 errmsg("alignment \"%c\" is invalid for variable-length type",
							alignment)));
		/* cstring must have char alignment */
		if (internalSize == -2 && !(alignment == 'c'))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
					 errmsg("alignment \"%c\" is invalid for variable-length type",
							alignment)));
	}

	/* Only varlena types can be toasted */
	if (storage != 'p' && internalSize != -1)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
				 errmsg("fixed-size types must have storage PLAIN")));

	/*
	 * This is a dependent type if it's an implicitly-created array type, or
	 * if it's a relation rowtype that's not a composite type.  For such types
	 * we'll leave the ACL empty, and we'll skip creating some dependency
	 * records because there will be a dependency already through the
	 * depended-on type or relation.  (Caution: this is closely intertwined
	 * with some behavior in GenerateTypeDependencies.)
	 */
	isDependentType = isImplicitArray ||
		(OidIsValid(relationOid) && relationKind != RELKIND_COMPOSITE_TYPE);

	/*
	 * initialize arrays needed for heap_form_tuple or heap_modify_tuple
	 */
	for (i = 0; i < Natts_pg_type; ++i)
	{
		nulls[i] = false;
		replaces[i] = true;
		values[i] = (Datum) 0;
	}

	/*
	 * insert data values
	 */
	namestrcpy(&name, typeName);
	values[Anum_pg_type_typname - 1] = NameGetDatum(&name);
	values[Anum_pg_type_typnamespace - 1] = ObjectIdGetDatum(typeNamespace);
	values[Anum_pg_type_typowner - 1] = ObjectIdGetDatum(ownerId);
	values[Anum_pg_type_typlen - 1] = Int16GetDatum(internalSize);
	values[Anum_pg_type_typbyval - 1] = BoolGetDatum(passedByValue);
	values[Anum_pg_type_typtype - 1] = CharGetDatum(typeType);
	values[Anum_pg_type_typcategory - 1] = CharGetDatum(typeCategory);
	values[Anum_pg_type_typispreferred - 1] = BoolGetDatum(typePreferred);
	values[Anum_pg_type_typisdefined - 1] = BoolGetDatum(true);
	values[Anum_pg_type_typdelim - 1] = CharGetDatum(typDelim);
	values[Anum_pg_type_typrelid - 1] = ObjectIdGetDatum(relationOid);
	values[Anum_pg_type_typelem - 1] = ObjectIdGetDatum(elementType);
	values[Anum_pg_type_typarray - 1] = ObjectIdGetDatum(arrayType);
	values[Anum_pg_type_typinput - 1] = ObjectIdGetDatum(inputProcedure);
	values[Anum_pg_type_typoutput - 1] = ObjectIdGetDatum(outputProcedure);
	values[Anum_pg_type_typreceive - 1] = ObjectIdGetDatum(receiveProcedure);
	values[Anum_pg_type_typsend - 1] = ObjectIdGetDatum(sendProcedure);
	values[Anum_pg_type_typmodin - 1] = ObjectIdGetDatum(typmodinProcedure);
	values[Anum_pg_type_typmodout - 1] = ObjectIdGetDatum(typmodoutProcedure);
	values[Anum_pg_type_typanalyze - 1] = ObjectIdGetDatum(analyzeProcedure);
	values[Anum_pg_type_typalign - 1] = CharGetDatum(alignment);
	values[Anum_pg_type_typstorage - 1] = CharGetDatum(storage);
	values[Anum_pg_type_typnotnull - 1] = BoolGetDatum(typeNotNull);
	values[Anum_pg_type_typbasetype - 1] = ObjectIdGetDatum(baseType);
	values[Anum_pg_type_typtypmod - 1] = Int32GetDatum(typeMod);
	values[Anum_pg_type_typndims - 1] = Int32GetDatum(typNDims);
	values[Anum_pg_type_typcollation - 1] = ObjectIdGetDatum(typeCollation);

	/*
	 * initialize the default binary value for this type.  Check for nulls of
	 * course.
	 */
	if (defaultTypeBin)
		values[Anum_pg_type_typdefaultbin - 1] = CStringGetTextDatum(defaultTypeBin);
	else
		nulls[Anum_pg_type_typdefaultbin - 1] = true;

	/*
	 * initialize the default value for this type.
	 */
	if (defaultTypeValue)
		values[Anum_pg_type_typdefault - 1] = CStringGetTextDatum(defaultTypeValue);
	else
		nulls[Anum_pg_type_typdefault - 1] = true;

	/*
	 * Initialize the type's ACL, too.  But dependent types don't get one.
	 */
	if (isDependentType)
		typacl = NULL;
	else
		typacl = get_user_default_acl(OBJECT_TYPE, ownerId,
									  typeNamespace);
	if (typacl != NULL)
		values[Anum_pg_type_typacl - 1] = PointerGetDatum(typacl);
	else
		nulls[Anum_pg_type_typacl - 1] = true;

	/*
	 * open pg_type and prepare to insert or update a row.
	 *
	 * NOTE: updating will not work correctly in bootstrap mode; but we don't
	 * expect to be overwriting any shell types in bootstrap mode.
	 */
	pg_type_desc = table_open(TypeRelationId, RowExclusiveLock);

	tup = SearchSysCacheCopy2(TYPENAMENSP,
							  CStringGetDatum(typeName),
							  ObjectIdGetDatum(typeNamespace));
	if (HeapTupleIsValid(tup))
	{
		Form_pg_type typform = (Form_pg_type) GETSTRUCT(tup);

		/*
		 * check that the type is not already defined.  It may exist as a
		 * shell type, however.
		 */
		if (typform->typisdefined)
			ereport(ERROR,
					(errcode(ERRCODE_DUPLICATE_OBJECT),
					 errmsg("type \"%s\" already exists", typeName)));

		/*
		 * shell type must have been created by same owner
		 */
		if (typform->typowner != ownerId)
			aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_TYPE, typeName);

		/* trouble if caller wanted to force the OID */
		if (OidIsValid(newTypeOid))
			elog(ERROR, "cannot assign new OID to existing shell type");

		replaces[Anum_pg_type_oid - 1] = false;

		/*
		 * Okay to update existing shell type tuple
		 */
		tup = heap_modify_tuple(tup,
								RelationGetDescr(pg_type_desc),
								values,
								nulls,
								replaces);

		CatalogTupleUpdate(pg_type_desc, &tup->t_self, tup);

		typeObjectId = typform->oid;

		rebuildDeps = true;		/* get rid of shell type's dependencies */
	}
	else
	{
		/* Force the OID if requested by caller */
		if (OidIsValid(newTypeOid))
			typeObjectId = newTypeOid;
		/* Use binary-upgrade override for pg_type.oid, if supplied. */
		else if (IsBinaryUpgrade)
		{
			if (!OidIsValid(binary_upgrade_next_pg_type_oid))
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						 errmsg("pg_type OID value not set when in binary upgrade mode")));

			typeObjectId = binary_upgrade_next_pg_type_oid;
			binary_upgrade_next_pg_type_oid = InvalidOid;
		}
		else
		{
			typeObjectId = GetNewOidWithIndex(pg_type_desc, TypeOidIndexId,
											  Anum_pg_type_oid);
		}

		values[Anum_pg_type_oid - 1] = ObjectIdGetDatum(typeObjectId);

		tup = heap_form_tuple(RelationGetDescr(pg_type_desc),
							  values, nulls);

		CatalogTupleInsert(pg_type_desc, tup);
	}

	/*
	 * Create dependencies.  We can/must skip this in bootstrap mode.
	 */
	if (!IsBootstrapProcessingMode())
		GenerateTypeDependencies(typeObjectId,
								 (Form_pg_type) GETSTRUCT(tup),
								 (defaultTypeBin ?
								  stringToNode(defaultTypeBin) :
								  NULL),
								 typacl,
								 relationKind,
								 isImplicitArray,
								 isDependentType,
								 rebuildDeps);

	/* Post creation hook for new type */
	InvokeObjectPostCreateHook(TypeRelationId, typeObjectId, 0);

	ObjectAddressSet(address, TypeRelationId, typeObjectId);

	/*
	 * finish up
	 */
	table_close(pg_type_desc, RowExclusiveLock);

	return address;
}