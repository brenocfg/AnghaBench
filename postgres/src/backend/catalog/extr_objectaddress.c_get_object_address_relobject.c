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
struct TYPE_3__ {void* objectId; int /*<<< orphan*/  objectSubId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  void* Oid ;
typedef  int ObjectType ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  ConstraintRelationId ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 void* InvalidOid ; 
#define  OBJECT_POLICY 131 
#define  OBJECT_RULE 130 
#define  OBJECT_TABCONSTRAINT 129 
#define  OBJECT_TRIGGER 128 
 int /*<<< orphan*/  OidIsValid (void*) ; 
 int /*<<< orphan*/  PolicyRelationId ; 
 void* RelationGetRelid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RewriteRelationId ; 
 int /*<<< orphan*/  TriggerRelationId ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 void* get_relation_constraint_oid (void*,char const*,int) ; 
 void* get_relation_policy_oid (void*,char const*,int) ; 
 void* get_rewrite_oid (void*,char const*,int) ; 
 void* get_trigger_oid (void*,char const*,int) ; 
 int /*<<< orphan*/  list_copy (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_truncate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  llast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  makeRangeVarFromNameList (int /*<<< orphan*/ *) ; 
 char* strVal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * table_openrv_extended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ObjectAddress
get_object_address_relobject(ObjectType objtype, List *object,
							 Relation *relp, bool missing_ok)
{
	ObjectAddress address;
	Relation	relation = NULL;
	int			nnames;
	const char *depname;
	List	   *relname;
	Oid			reloid;

	/* Extract name of dependent object. */
	depname = strVal(llast(object));

	/* Separate relation name from dependent object name. */
	nnames = list_length(object);
	if (nnames < 2)
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("must specify relation and object name")));

	/* Extract relation name and open relation. */
	relname = list_truncate(list_copy(object), nnames - 1);
	relation = table_openrv_extended(makeRangeVarFromNameList(relname),
									 AccessShareLock,
									 missing_ok);

	reloid = relation ? RelationGetRelid(relation) : InvalidOid;

	switch (objtype)
	{
		case OBJECT_RULE:
			address.classId = RewriteRelationId;
			address.objectId = relation ?
				get_rewrite_oid(reloid, depname, missing_ok) : InvalidOid;
			address.objectSubId = 0;
			break;
		case OBJECT_TRIGGER:
			address.classId = TriggerRelationId;
			address.objectId = relation ?
				get_trigger_oid(reloid, depname, missing_ok) : InvalidOid;
			address.objectSubId = 0;
			break;
		case OBJECT_TABCONSTRAINT:
			address.classId = ConstraintRelationId;
			address.objectId = relation ?
				get_relation_constraint_oid(reloid, depname, missing_ok) :
				InvalidOid;
			address.objectSubId = 0;
			break;
		case OBJECT_POLICY:
			address.classId = PolicyRelationId;
			address.objectId = relation ?
				get_relation_policy_oid(reloid, depname, missing_ok) :
				InvalidOid;
			address.objectSubId = 0;
			break;
		default:
			elog(ERROR, "unrecognized objtype: %d", (int) objtype);
	}

	/* Avoid relcache leak when object not found. */
	if (!OidIsValid(address.objectId))
	{
		if (relation != NULL)
			table_close(relation, AccessShareLock);

		relation = NULL;		/* department of accident prevention */
		return address;
	}

	/* Done. */
	*relp = relation;
	return address;
}