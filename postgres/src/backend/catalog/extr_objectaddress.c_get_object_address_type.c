#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TypeName ;
typedef  int /*<<< orphan*/  Type ;
struct TYPE_5__ {scalar_t__ typtype; } ;
struct TYPE_4__ {int /*<<< orphan*/  objectId; scalar_t__ objectSubId; int /*<<< orphan*/  classId; } ;
typedef  scalar_t__ ObjectType ;
typedef  TYPE_1__ ObjectAddress ;
typedef  TYPE_2__* Form_pg_type ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  LookupTypeName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ OBJECT_DOMAIN ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPTYPE_DOMAIN ; 
 int /*<<< orphan*/  TypeNameToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TypeRelationId ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typeTypeId (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ObjectAddress
get_object_address_type(ObjectType objtype, TypeName *typename, bool missing_ok)
{
	ObjectAddress address;
	Type		tup;

	address.classId = TypeRelationId;
	address.objectId = InvalidOid;
	address.objectSubId = 0;

	tup = LookupTypeName(NULL, typename, NULL, missing_ok);
	if (!HeapTupleIsValid(tup))
	{
		if (!missing_ok)
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("type \"%s\" does not exist",
							TypeNameToString(typename))));
		return address;
	}
	address.objectId = typeTypeId(tup);

	if (objtype == OBJECT_DOMAIN)
	{
		if (((Form_pg_type) GETSTRUCT(tup))->typtype != TYPTYPE_DOMAIN)
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("\"%s\" is not a domain",
							TypeNameToString(typename))));
	}

	ReleaseSysCache(tup);

	return address;
}