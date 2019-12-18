#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ objectSubId; int /*<<< orphan*/  objectId; void* classId; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ObjectType ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_COLUMN ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidAttrNumber ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  NameListToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 void* RelationRelationId ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ get_attnum (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  lfirst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_copy (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_truncate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  makeRangeVarFromNameList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_openrv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strVal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ObjectAddress
get_object_address_attribute(ObjectType objtype, List *object,
							 Relation *relp, LOCKMODE lockmode,
							 bool missing_ok)
{
	ObjectAddress address;
	List	   *relname;
	Oid			reloid;
	Relation	relation;
	const char *attname;
	AttrNumber	attnum;

	/* Extract relation name and open relation. */
	if (list_length(object) < 2)
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("column name must be qualified")));
	attname = strVal(lfirst(list_tail(object)));
	relname = list_truncate(list_copy(object), list_length(object) - 1);
	/* XXX no missing_ok support here */
	relation = relation_openrv(makeRangeVarFromNameList(relname), lockmode);
	reloid = RelationGetRelid(relation);

	/* Look up attribute and construct return value. */
	attnum = get_attnum(reloid, attname);
	if (attnum == InvalidAttrNumber)
	{
		if (!missing_ok)
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_COLUMN),
					 errmsg("column \"%s\" of relation \"%s\" does not exist",
							attname, NameListToString(relname))));

		address.classId = RelationRelationId;
		address.objectId = InvalidOid;
		address.objectSubId = InvalidAttrNumber;
		relation_close(relation, lockmode);
		return address;
	}

	address.classId = RelationRelationId;
	address.objectId = reloid;
	address.objectSubId = attnum;

	*relp = relation;
	return address;
}