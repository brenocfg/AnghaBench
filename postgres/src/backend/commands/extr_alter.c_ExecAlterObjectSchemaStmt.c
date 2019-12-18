#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Value ;
struct TYPE_14__ {int objectType; int /*<<< orphan*/  newschema; scalar_t__ object; } ;
struct TYPE_13__ {int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  TYPE_2__ AlterObjectSchemaStmt ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 TYPE_1__ AlterExtensionNamespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AlterObjectNamespace_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ AlterTableNamespace (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_1__ AlterTypeNamespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__ InvalidObjectAddress ; 
 int /*<<< orphan*/  List ; 
 int /*<<< orphan*/  LookupCreationNamespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NamespaceRelationId ; 
#define  OBJECT_AGGREGATE 149 
#define  OBJECT_COLLATION 148 
#define  OBJECT_CONVERSION 147 
#define  OBJECT_DOMAIN 146 
#define  OBJECT_EXTENSION 145 
#define  OBJECT_FOREIGN_TABLE 144 
#define  OBJECT_FUNCTION 143 
#define  OBJECT_MATVIEW 142 
#define  OBJECT_OPCLASS 141 
#define  OBJECT_OPERATOR 140 
#define  OBJECT_OPFAMILY 139 
#define  OBJECT_PROCEDURE 138 
#define  OBJECT_ROUTINE 137 
#define  OBJECT_SEQUENCE 136 
#define  OBJECT_STATISTIC_EXT 135 
#define  OBJECT_TABLE 134 
#define  OBJECT_TSCONFIGURATION 133 
#define  OBJECT_TSDICTIONARY 132 
#define  OBJECT_TSPARSER 131 
#define  OBJECT_TSTEMPLATE 130 
#define  OBJECT_TYPE 129 
#define  OBJECT_VIEW 128 
 int /*<<< orphan*/  ObjectAddressSet (TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  castNode (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__ get_object_address (int,scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ObjectAddress
ExecAlterObjectSchemaStmt(AlterObjectSchemaStmt *stmt,
						  ObjectAddress *oldSchemaAddr)
{
	ObjectAddress address;
	Oid			oldNspOid;

	switch (stmt->objectType)
	{
		case OBJECT_EXTENSION:
			address = AlterExtensionNamespace(strVal((Value *) stmt->object), stmt->newschema,
											  oldSchemaAddr ? &oldNspOid : NULL);
			break;

		case OBJECT_FOREIGN_TABLE:
		case OBJECT_SEQUENCE:
		case OBJECT_TABLE:
		case OBJECT_VIEW:
		case OBJECT_MATVIEW:
			address = AlterTableNamespace(stmt,
										  oldSchemaAddr ? &oldNspOid : NULL);
			break;

		case OBJECT_DOMAIN:
		case OBJECT_TYPE:
			address = AlterTypeNamespace(castNode(List, stmt->object), stmt->newschema,
										 stmt->objectType,
										 oldSchemaAddr ? &oldNspOid : NULL);
			break;

			/* generic code path */
		case OBJECT_AGGREGATE:
		case OBJECT_COLLATION:
		case OBJECT_CONVERSION:
		case OBJECT_FUNCTION:
		case OBJECT_OPERATOR:
		case OBJECT_OPCLASS:
		case OBJECT_OPFAMILY:
		case OBJECT_PROCEDURE:
		case OBJECT_ROUTINE:
		case OBJECT_STATISTIC_EXT:
		case OBJECT_TSCONFIGURATION:
		case OBJECT_TSDICTIONARY:
		case OBJECT_TSPARSER:
		case OBJECT_TSTEMPLATE:
			{
				Relation	catalog;
				Relation	relation;
				Oid			classId;
				Oid			nspOid;

				address = get_object_address(stmt->objectType,
											 stmt->object,
											 &relation,
											 AccessExclusiveLock,
											 false);
				Assert(relation == NULL);
				classId = address.classId;
				catalog = table_open(classId, RowExclusiveLock);
				nspOid = LookupCreationNamespace(stmt->newschema);

				oldNspOid = AlterObjectNamespace_internal(catalog, address.objectId,
														  nspOid);
				table_close(catalog, RowExclusiveLock);
			}
			break;

		default:
			elog(ERROR, "unrecognized AlterObjectSchemaStmt type: %d",
				 (int) stmt->objectType);
			return InvalidObjectAddress;	/* keep compiler happy */
	}

	if (oldSchemaAddr)
		ObjectAddressSet(*oldSchemaAddr, NamespaceRelationId, oldNspOid);

	return address;
}