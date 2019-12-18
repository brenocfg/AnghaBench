#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
struct TYPE_24__ {int renameType; int /*<<< orphan*/  newname; int /*<<< orphan*/  object; int /*<<< orphan*/  subname; int /*<<< orphan*/  relation; } ;
typedef  TYPE_1__ RenameStmt ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  TYPE_2__ ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  AlterObjectRename_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_2__ InvalidObjectAddress ; 
#define  OBJECT_AGGREGATE 165 
#define  OBJECT_ATTRIBUTE 164 
#define  OBJECT_COLLATION 163 
#define  OBJECT_COLUMN 162 
#define  OBJECT_CONVERSION 161 
#define  OBJECT_DATABASE 160 
#define  OBJECT_DOMAIN 159 
#define  OBJECT_DOMCONSTRAINT 158 
#define  OBJECT_EVENT_TRIGGER 157 
#define  OBJECT_FDW 156 
#define  OBJECT_FOREIGN_SERVER 155 
#define  OBJECT_FOREIGN_TABLE 154 
#define  OBJECT_FUNCTION 153 
#define  OBJECT_INDEX 152 
#define  OBJECT_LANGUAGE 151 
#define  OBJECT_MATVIEW 150 
#define  OBJECT_OPCLASS 149 
#define  OBJECT_OPFAMILY 148 
#define  OBJECT_POLICY 147 
#define  OBJECT_PROCEDURE 146 
#define  OBJECT_PUBLICATION 145 
#define  OBJECT_ROLE 144 
#define  OBJECT_ROUTINE 143 
#define  OBJECT_RULE 142 
#define  OBJECT_SCHEMA 141 
#define  OBJECT_SEQUENCE 140 
#define  OBJECT_STATISTIC_EXT 139 
#define  OBJECT_SUBSCRIPTION 138 
#define  OBJECT_TABCONSTRAINT 137 
#define  OBJECT_TABLE 136 
#define  OBJECT_TABLESPACE 135 
#define  OBJECT_TRIGGER 134 
#define  OBJECT_TSCONFIGURATION 133 
#define  OBJECT_TSDICTIONARY 132 
#define  OBJECT_TSPARSER 131 
#define  OBJECT_TSTEMPLATE 130 
#define  OBJECT_TYPE 129 
#define  OBJECT_VIEW 128 
 TYPE_2__ RenameConstraint (TYPE_1__*) ; 
 TYPE_2__ RenameDatabase (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ RenameRelation (TYPE_1__*) ; 
 TYPE_2__ RenameRewriteRule (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ RenameRole (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ RenameSchema (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ RenameTableSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ RenameType (TYPE_1__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__ get_object_address (int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ rename_policy (TYPE_1__*) ; 
 TYPE_2__ renameatt (TYPE_1__*) ; 
 TYPE_2__ renametrig (TYPE_1__*) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ObjectAddress
ExecRenameStmt(RenameStmt *stmt)
{
	switch (stmt->renameType)
	{
		case OBJECT_TABCONSTRAINT:
		case OBJECT_DOMCONSTRAINT:
			return RenameConstraint(stmt);

		case OBJECT_DATABASE:
			return RenameDatabase(stmt->subname, stmt->newname);

		case OBJECT_ROLE:
			return RenameRole(stmt->subname, stmt->newname);

		case OBJECT_SCHEMA:
			return RenameSchema(stmt->subname, stmt->newname);

		case OBJECT_TABLESPACE:
			return RenameTableSpace(stmt->subname, stmt->newname);

		case OBJECT_TABLE:
		case OBJECT_SEQUENCE:
		case OBJECT_VIEW:
		case OBJECT_MATVIEW:
		case OBJECT_INDEX:
		case OBJECT_FOREIGN_TABLE:
			return RenameRelation(stmt);

		case OBJECT_COLUMN:
		case OBJECT_ATTRIBUTE:
			return renameatt(stmt);

		case OBJECT_RULE:
			return RenameRewriteRule(stmt->relation, stmt->subname,
									 stmt->newname);

		case OBJECT_TRIGGER:
			return renametrig(stmt);

		case OBJECT_POLICY:
			return rename_policy(stmt);

		case OBJECT_DOMAIN:
		case OBJECT_TYPE:
			return RenameType(stmt);

		case OBJECT_AGGREGATE:
		case OBJECT_COLLATION:
		case OBJECT_CONVERSION:
		case OBJECT_EVENT_TRIGGER:
		case OBJECT_FDW:
		case OBJECT_FOREIGN_SERVER:
		case OBJECT_FUNCTION:
		case OBJECT_OPCLASS:
		case OBJECT_OPFAMILY:
		case OBJECT_LANGUAGE:
		case OBJECT_PROCEDURE:
		case OBJECT_ROUTINE:
		case OBJECT_STATISTIC_EXT:
		case OBJECT_TSCONFIGURATION:
		case OBJECT_TSDICTIONARY:
		case OBJECT_TSPARSER:
		case OBJECT_TSTEMPLATE:
		case OBJECT_PUBLICATION:
		case OBJECT_SUBSCRIPTION:
			{
				ObjectAddress address;
				Relation	catalog;
				Relation	relation;

				address = get_object_address(stmt->renameType,
											 stmt->object,
											 &relation,
											 AccessExclusiveLock, false);
				Assert(relation == NULL);

				catalog = table_open(address.classId, RowExclusiveLock);
				AlterObjectRename_internal(catalog,
										   address.objectId,
										   stmt->newname);
				table_close(catalog, RowExclusiveLock);

				return address;
			}

		default:
			elog(ERROR, "unrecognized rename stmt type: %d",
				 (int) stmt->renameType);
			return InvalidObjectAddress;	/* keep compiler happy */
	}
}