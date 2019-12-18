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
struct TYPE_8__ {scalar_t__ oid; } ;
struct TYPE_7__ {int /*<<< orphan*/  oid; } ;
struct TYPE_6__ {int /*<<< orphan*/  objectId; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_default_acl ;
typedef  TYPE_3__* Form_pg_authid ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHNAME ; 
 int /*<<< orphan*/  CStringGetDatum (char*) ; 
 int /*<<< orphan*/  CharGetDatum (char) ; 
#define  DEFACLOBJ_FUNCTION 132 
#define  DEFACLOBJ_NAMESPACE 131 
#define  DEFACLOBJ_RELATION 130 
#define  DEFACLOBJ_SEQUENCE 129 
#define  DEFACLOBJ_TYPE 128 
 int /*<<< orphan*/  DEFACLROLENSPOBJ ; 
 int /*<<< orphan*/  DefaultAclRelationId ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  ObjectAddressSet (TYPE_1__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,int const,int const,int const,int const,int const) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ get_namespace_oid (char*,int) ; 
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsecond (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lthird (int /*<<< orphan*/ *) ; 
 char* strVal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ObjectAddress
get_object_address_defacl(List *object, bool missing_ok)
{
	HeapTuple	tp;
	Oid			userid;
	Oid			schemaid;
	char	   *username;
	char	   *schema;
	char		objtype;
	char	   *objtype_str;
	ObjectAddress address;

	ObjectAddressSet(address, DefaultAclRelationId, InvalidOid);

	/*
	 * First figure out the textual attributes so that they can be used for
	 * error reporting.
	 */
	username = strVal(lsecond(object));
	if (list_length(object) >= 3)
		schema = (char *) strVal(lthird(object));
	else
		schema = NULL;

	/*
	 * Decode defaclobjtype.  Only first char is considered; the rest of the
	 * string, if any, is blissfully ignored.
	 */
	objtype = ((char *) strVal(linitial(object)))[0];
	switch (objtype)
	{
		case DEFACLOBJ_RELATION:
			objtype_str = "tables";
			break;
		case DEFACLOBJ_SEQUENCE:
			objtype_str = "sequences";
			break;
		case DEFACLOBJ_FUNCTION:
			objtype_str = "functions";
			break;
		case DEFACLOBJ_TYPE:
			objtype_str = "types";
			break;
		case DEFACLOBJ_NAMESPACE:
			objtype_str = "schemas";
			break;
		default:
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("unrecognized default ACL object type \"%c\"", objtype),
					 errhint("Valid object types are \"%c\", \"%c\", \"%c\", \"%c\", \"%c\".",
							 DEFACLOBJ_RELATION,
							 DEFACLOBJ_SEQUENCE,
							 DEFACLOBJ_FUNCTION,
							 DEFACLOBJ_TYPE,
							 DEFACLOBJ_NAMESPACE)));
	}

	/*
	 * Look up user ID.  Behave as "default ACL not found" if the user doesn't
	 * exist.
	 */
	tp = SearchSysCache1(AUTHNAME,
						 CStringGetDatum(username));
	if (!HeapTupleIsValid(tp))
		goto not_found;
	userid = ((Form_pg_authid) GETSTRUCT(tp))->oid;
	ReleaseSysCache(tp);

	/*
	 * If a schema name was given, look up its OID.  If it doesn't exist,
	 * behave as "default ACL not found".
	 */
	if (schema)
	{
		schemaid = get_namespace_oid(schema, true);
		if (schemaid == InvalidOid)
			goto not_found;
	}
	else
		schemaid = InvalidOid;

	/* Finally, look up the pg_default_acl object */
	tp = SearchSysCache3(DEFACLROLENSPOBJ,
						 ObjectIdGetDatum(userid),
						 ObjectIdGetDatum(schemaid),
						 CharGetDatum(objtype));
	if (!HeapTupleIsValid(tp))
		goto not_found;

	address.objectId = ((Form_pg_default_acl) GETSTRUCT(tp))->oid;
	ReleaseSysCache(tp);

	return address;

not_found:
	if (!missing_ok)
	{
		if (schema)
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("default ACL for user \"%s\" in schema \"%s\" on %s does not exist",
							username, schema, objtype_str)));
		else
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("default ACL for user \"%s\" on %s does not exist",
							username, objtype_str)));
	}
	return address;
}