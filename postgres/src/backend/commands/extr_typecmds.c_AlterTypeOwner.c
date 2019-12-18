#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TypeName ;
struct TYPE_2__ {scalar_t__ typtype; scalar_t__ typelem; scalar_t__ typowner; int /*<<< orphan*/  typnamespace; int /*<<< orphan*/  oid; int /*<<< orphan*/  typrelid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  scalar_t__ ObjectType ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_1__* Form_pg_type ;
typedef  scalar_t__ AclResult ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_CREATE ; 
 int /*<<< orphan*/  AlterTypeOwner_oid (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/ * LookupTypeName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ OBJECT_DOMAIN ; 
 int /*<<< orphan*/  OBJECT_SCHEMA ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 scalar_t__ RELKIND_COMPOSITE_TYPE ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 scalar_t__ TYPTYPE_COMPOSITE ; 
 scalar_t__ TYPTYPE_DOMAIN ; 
 int /*<<< orphan*/  TypeNameToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TypeRelationId ; 
 int /*<<< orphan*/  aclcheck_error (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aclcheck_error_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_is_member_of_role (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,...) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (scalar_t__) ; 
 scalar_t__ get_array_type (scalar_t__) ; 
 int /*<<< orphan*/  get_namespace_name (int /*<<< orphan*/ ) ; 
 scalar_t__ get_rel_relkind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_copytuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * makeTypeNameFromNameList (int /*<<< orphan*/ *) ; 
 scalar_t__ pg_namespace_aclcheck (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_type_ownercheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superuser () ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ typeTypeId (int /*<<< orphan*/ *) ; 

ObjectAddress
AlterTypeOwner(List *names, Oid newOwnerId, ObjectType objecttype)
{
	TypeName   *typename;
	Oid			typeOid;
	Relation	rel;
	HeapTuple	tup;
	HeapTuple	newtup;
	Form_pg_type typTup;
	AclResult	aclresult;
	ObjectAddress address;

	rel = table_open(TypeRelationId, RowExclusiveLock);

	/* Make a TypeName so we can use standard type lookup machinery */
	typename = makeTypeNameFromNameList(names);

	/* Use LookupTypeName here so that shell types can be processed */
	tup = LookupTypeName(NULL, typename, NULL, false);
	if (tup == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("type \"%s\" does not exist",
						TypeNameToString(typename))));
	typeOid = typeTypeId(tup);

	/* Copy the syscache entry so we can scribble on it below */
	newtup = heap_copytuple(tup);
	ReleaseSysCache(tup);
	tup = newtup;
	typTup = (Form_pg_type) GETSTRUCT(tup);

	/* Don't allow ALTER DOMAIN on a type */
	if (objecttype == OBJECT_DOMAIN && typTup->typtype != TYPTYPE_DOMAIN)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("%s is not a domain",
						format_type_be(typeOid))));

	/*
	 * If it's a composite type, we need to check that it really is a
	 * free-standing composite type, and not a table's rowtype. We want people
	 * to use ALTER TABLE not ALTER TYPE for that case.
	 */
	if (typTup->typtype == TYPTYPE_COMPOSITE &&
		get_rel_relkind(typTup->typrelid) != RELKIND_COMPOSITE_TYPE)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("%s is a table's row type",
						format_type_be(typeOid)),
				 errhint("Use ALTER TABLE instead.")));

	/* don't allow direct alteration of array types, either */
	if (OidIsValid(typTup->typelem) &&
		get_array_type(typTup->typelem) == typeOid)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot alter array type %s",
						format_type_be(typeOid)),
				 errhint("You can alter type %s, which will alter the array type as well.",
						 format_type_be(typTup->typelem))));

	/*
	 * If the new owner is the same as the existing owner, consider the
	 * command to have succeeded.  This is for dump restoration purposes.
	 */
	if (typTup->typowner != newOwnerId)
	{
		/* Superusers can always do it */
		if (!superuser())
		{
			/* Otherwise, must be owner of the existing object */
			if (!pg_type_ownercheck(typTup->oid, GetUserId()))
				aclcheck_error_type(ACLCHECK_NOT_OWNER, typTup->oid);

			/* Must be able to become new owner */
			check_is_member_of_role(GetUserId(), newOwnerId);

			/* New owner must have CREATE privilege on namespace */
			aclresult = pg_namespace_aclcheck(typTup->typnamespace,
											  newOwnerId,
											  ACL_CREATE);
			if (aclresult != ACLCHECK_OK)
				aclcheck_error(aclresult, OBJECT_SCHEMA,
							   get_namespace_name(typTup->typnamespace));
		}

		AlterTypeOwner_oid(typeOid, newOwnerId, true);
	}

	ObjectAddressSet(address, TypeRelationId, typeOid);

	/* Clean up */
	table_close(rel, RowExclusiveLock);

	return address;
}