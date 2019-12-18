#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Value ;
struct TYPE_16__ {int objectType; scalar_t__ object; int /*<<< orphan*/  newowner; } ;
struct TYPE_15__ {int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  TYPE_2__ AlterOwnerStmt ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 TYPE_1__ AlterDatabaseOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ AlterEventTriggerOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ AlterForeignDataWrapperOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ AlterForeignServerOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AlterObjectOwner_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ AlterPublicationOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ AlterSchemaOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ AlterSubscriptionOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ AlterTypeOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__ InvalidObjectAddress ; 
 int /*<<< orphan*/  LargeObjectMetadataRelationId ; 
 int /*<<< orphan*/  LargeObjectRelationId ; 
 int /*<<< orphan*/  List ; 
#define  OBJECT_AGGREGATE 151 
#define  OBJECT_COLLATION 150 
#define  OBJECT_CONVERSION 149 
#define  OBJECT_DATABASE 148 
#define  OBJECT_DOMAIN 147 
#define  OBJECT_EVENT_TRIGGER 146 
#define  OBJECT_FDW 145 
#define  OBJECT_FOREIGN_SERVER 144 
#define  OBJECT_FUNCTION 143 
#define  OBJECT_LANGUAGE 142 
#define  OBJECT_LARGEOBJECT 141 
#define  OBJECT_OPCLASS 140 
#define  OBJECT_OPERATOR 139 
#define  OBJECT_OPFAMILY 138 
#define  OBJECT_PROCEDURE 137 
#define  OBJECT_PUBLICATION 136 
#define  OBJECT_ROUTINE 135 
#define  OBJECT_SCHEMA 134 
#define  OBJECT_STATISTIC_EXT 133 
#define  OBJECT_SUBSCRIPTION 132 
#define  OBJECT_TABLESPACE 131 
#define  OBJECT_TSCONFIGURATION 130 
#define  OBJECT_TSDICTIONARY 129 
#define  OBJECT_TYPE 128 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  castNode (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__ get_object_address (int,scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_rolespec_oid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ObjectAddress
ExecAlterOwnerStmt(AlterOwnerStmt *stmt)
{
	Oid			newowner = get_rolespec_oid(stmt->newowner, false);

	switch (stmt->objectType)
	{
		case OBJECT_DATABASE:
			return AlterDatabaseOwner(strVal((Value *) stmt->object), newowner);

		case OBJECT_SCHEMA:
			return AlterSchemaOwner(strVal((Value *) stmt->object), newowner);

		case OBJECT_TYPE:
		case OBJECT_DOMAIN:		/* same as TYPE */
			return AlterTypeOwner(castNode(List, stmt->object), newowner, stmt->objectType);
			break;

		case OBJECT_FDW:
			return AlterForeignDataWrapperOwner(strVal((Value *) stmt->object),
												newowner);

		case OBJECT_FOREIGN_SERVER:
			return AlterForeignServerOwner(strVal((Value *) stmt->object),
										   newowner);

		case OBJECT_EVENT_TRIGGER:
			return AlterEventTriggerOwner(strVal((Value *) stmt->object),
										  newowner);

		case OBJECT_PUBLICATION:
			return AlterPublicationOwner(strVal((Value *) stmt->object),
										 newowner);

		case OBJECT_SUBSCRIPTION:
			return AlterSubscriptionOwner(strVal((Value *) stmt->object),
										  newowner);

			/* Generic cases */
		case OBJECT_AGGREGATE:
		case OBJECT_COLLATION:
		case OBJECT_CONVERSION:
		case OBJECT_FUNCTION:
		case OBJECT_LANGUAGE:
		case OBJECT_LARGEOBJECT:
		case OBJECT_OPERATOR:
		case OBJECT_OPCLASS:
		case OBJECT_OPFAMILY:
		case OBJECT_PROCEDURE:
		case OBJECT_ROUTINE:
		case OBJECT_STATISTIC_EXT:
		case OBJECT_TABLESPACE:
		case OBJECT_TSDICTIONARY:
		case OBJECT_TSCONFIGURATION:
			{
				Relation	catalog;
				Relation	relation;
				Oid			classId;
				ObjectAddress address;

				address = get_object_address(stmt->objectType,
											 stmt->object,
											 &relation,
											 AccessExclusiveLock,
											 false);
				Assert(relation == NULL);
				classId = address.classId;

				/*
				 * XXX - get_object_address returns Oid of pg_largeobject
				 * catalog for OBJECT_LARGEOBJECT because of historical
				 * reasons.  Fix up it here.
				 */
				if (classId == LargeObjectRelationId)
					classId = LargeObjectMetadataRelationId;

				catalog = table_open(classId, RowExclusiveLock);

				AlterObjectOwner_internal(catalog, address.objectId, newowner);
				table_close(catalog, RowExclusiveLock);

				return address;
			}
			break;

		default:
			elog(ERROR, "unrecognized AlterOwnerStmt type: %d",
				 (int) stmt->objectType);
			return InvalidObjectAddress;	/* keep compiler happy */
	}
}