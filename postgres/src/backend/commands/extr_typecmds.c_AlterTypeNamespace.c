#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TypeName ;
typedef  int /*<<< orphan*/  Oid ;
typedef  scalar_t__ ObjectType ;
typedef  int /*<<< orphan*/  ObjectAddresses ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  AlterTypeNamespace_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  LookupCreationNamespace (char const*) ; 
 scalar_t__ OBJECT_DOMAIN ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TYPTYPE_DOMAIN ; 
 int /*<<< orphan*/  TypeRelationId ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_object_addresses (int /*<<< orphan*/ *) ; 
 scalar_t__ get_typtype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeTypeNameFromNameList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_object_addresses () ; 
 int /*<<< orphan*/  typenameTypeId (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ObjectAddress
AlterTypeNamespace(List *names, const char *newschema, ObjectType objecttype,
				   Oid *oldschema)
{
	TypeName   *typename;
	Oid			typeOid;
	Oid			nspOid;
	Oid			oldNspOid;
	ObjectAddresses *objsMoved;
	ObjectAddress myself;

	/* Make a TypeName so we can use standard type lookup machinery */
	typename = makeTypeNameFromNameList(names);
	typeOid = typenameTypeId(NULL, typename);

	/* Don't allow ALTER DOMAIN on a type */
	if (objecttype == OBJECT_DOMAIN && get_typtype(typeOid) != TYPTYPE_DOMAIN)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("%s is not a domain",
						format_type_be(typeOid))));

	/* get schema OID and check its permissions */
	nspOid = LookupCreationNamespace(newschema);

	objsMoved = new_object_addresses();
	oldNspOid = AlterTypeNamespace_oid(typeOid, nspOid, objsMoved);
	free_object_addresses(objsMoved);

	if (oldschema)
		*oldschema = oldNspOid;

	ObjectAddressSet(myself, TypeRelationId, typeOid);

	return myself;
}