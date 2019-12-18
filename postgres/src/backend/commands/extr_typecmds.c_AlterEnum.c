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
typedef  int /*<<< orphan*/  TypeName ;
struct TYPE_3__ {int /*<<< orphan*/  skipIfNewValExists; int /*<<< orphan*/  newValIsAfter; int /*<<< orphan*/  newValNeighbor; int /*<<< orphan*/  newVal; int /*<<< orphan*/  oldVal; int /*<<< orphan*/  typeName; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__ AlterEnumStmt ;

/* Variables and functions */
 int /*<<< orphan*/  AddEnumLabel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RenameEnumLabel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPEOID ; 
 int /*<<< orphan*/  TypeRelationId ; 
 int /*<<< orphan*/  checkEnumOwner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeTypeNameFromNameList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typenameTypeId (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ObjectAddress
AlterEnum(AlterEnumStmt *stmt)
{
	Oid			enum_type_oid;
	TypeName   *typename;
	HeapTuple	tup;
	ObjectAddress address;

	/* Make a TypeName so we can use standard type lookup machinery */
	typename = makeTypeNameFromNameList(stmt->typeName);
	enum_type_oid = typenameTypeId(NULL, typename);

	tup = SearchSysCache1(TYPEOID, ObjectIdGetDatum(enum_type_oid));
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for type %u", enum_type_oid);

	/* Check it's an enum and check user has permission to ALTER the enum */
	checkEnumOwner(tup);

	ReleaseSysCache(tup);

	if (stmt->oldVal)
	{
		/* Rename an existing label */
		RenameEnumLabel(enum_type_oid, stmt->oldVal, stmt->newVal);
	}
	else
	{
		/* Add a new label */
		AddEnumLabel(enum_type_oid, stmt->newVal,
					 stmt->newValNeighbor, stmt->newValIsAfter,
					 stmt->skipIfNewValExists);
	}

	InvokeObjectPostAlterHook(TypeRelationId, enum_type_oid, 0);

	ObjectAddressSet(address, TypeRelationId, enum_type_oid);

	return address;
}