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
typedef  TYPE_1__* TupleDesc ;
struct TYPE_8__ {void* oid; } ;
struct TYPE_7__ {scalar_t__ objectSubId; void* objectId; void* classId; } ;
struct TYPE_6__ {int /*<<< orphan*/ * constr; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  void* Oid ;
typedef  int /*<<< orphan*/  ObjectType ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_attrdef ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_attrdef_adnum ; 
 int /*<<< orphan*/  Anum_pg_attrdef_adrelid ; 
 int /*<<< orphan*/  AttrDefaultIndexId ; 
 void* AttrDefaultRelationId ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_COLUMN ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_INT2EQ ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int16GetDatum (scalar_t__) ; 
 scalar_t__ InvalidAttrNumber ; 
 void* InvalidOid ; 
 int /*<<< orphan*/  NameListToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (void*) ; 
 int /*<<< orphan*/  OidIsValid (void*) ; 
 TYPE_1__* RelationGetDescr (int /*<<< orphan*/ ) ; 
 void* RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ get_attnum (void*,char const*) ; 
 int /*<<< orphan*/  list_copy (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_truncate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  llast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  makeRangeVarFromNameList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_open (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_openrv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strVal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ObjectAddress
get_object_address_attrdef(ObjectType objtype, List *object,
						   Relation *relp, LOCKMODE lockmode,
						   bool missing_ok)
{
	ObjectAddress address;
	List	   *relname;
	Oid			reloid;
	Relation	relation;
	const char *attname;
	AttrNumber	attnum;
	TupleDesc	tupdesc;
	Oid			defoid;

	/* Extract relation name and open relation. */
	if (list_length(object) < 2)
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("column name must be qualified")));
	attname = strVal(llast(object));
	relname = list_truncate(list_copy(object), list_length(object) - 1);
	/* XXX no missing_ok support here */
	relation = relation_openrv(makeRangeVarFromNameList(relname), lockmode);
	reloid = RelationGetRelid(relation);

	tupdesc = RelationGetDescr(relation);

	/* Look up attribute number and scan pg_attrdef to find its tuple */
	attnum = get_attnum(reloid, attname);
	defoid = InvalidOid;
	if (attnum != InvalidAttrNumber && tupdesc->constr != NULL)
	{
		Relation	attrdef;
		ScanKeyData keys[2];
		SysScanDesc scan;
		HeapTuple	tup;

		attrdef = relation_open(AttrDefaultRelationId, AccessShareLock);
		ScanKeyInit(&keys[0],
					Anum_pg_attrdef_adrelid,
					BTEqualStrategyNumber,
					F_OIDEQ,
					ObjectIdGetDatum(reloid));
		ScanKeyInit(&keys[1],
					Anum_pg_attrdef_adnum,
					BTEqualStrategyNumber,
					F_INT2EQ,
					Int16GetDatum(attnum));
		scan = systable_beginscan(attrdef, AttrDefaultIndexId, true,
								  NULL, 2, keys);
		if (HeapTupleIsValid(tup = systable_getnext(scan)))
		{
			Form_pg_attrdef atdform = (Form_pg_attrdef) GETSTRUCT(tup);

			defoid = atdform->oid;
		}

		systable_endscan(scan);
		relation_close(attrdef, AccessShareLock);
	}
	if (!OidIsValid(defoid))
	{
		if (!missing_ok)
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_COLUMN),
					 errmsg("default value for column \"%s\" of relation \"%s\" does not exist",
							attname, NameListToString(relname))));

		address.classId = AttrDefaultRelationId;
		address.objectId = InvalidOid;
		address.objectSubId = InvalidAttrNumber;
		relation_close(relation, lockmode);
		return address;
	}

	address.classId = AttrDefaultRelationId;
	address.objectId = defoid;
	address.objectSubId = 0;

	*relp = relation;
	return address;
}