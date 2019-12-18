#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int objtype; } ;
typedef  TYPE_1__ InternalGrant ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EventTriggerCollectGrant (TYPE_1__*) ; 
 scalar_t__ EventTriggerSupportsObjectType (int) ; 
 int /*<<< orphan*/  ExecGrant_Database (TYPE_1__*) ; 
 int /*<<< orphan*/  ExecGrant_Fdw (TYPE_1__*) ; 
 int /*<<< orphan*/  ExecGrant_ForeignServer (TYPE_1__*) ; 
 int /*<<< orphan*/  ExecGrant_Function (TYPE_1__*) ; 
 int /*<<< orphan*/  ExecGrant_Language (TYPE_1__*) ; 
 int /*<<< orphan*/  ExecGrant_Largeobject (TYPE_1__*) ; 
 int /*<<< orphan*/  ExecGrant_Namespace (TYPE_1__*) ; 
 int /*<<< orphan*/  ExecGrant_Relation (TYPE_1__*) ; 
 int /*<<< orphan*/  ExecGrant_Tablespace (TYPE_1__*) ; 
 int /*<<< orphan*/  ExecGrant_Type (TYPE_1__*) ; 
#define  OBJECT_DATABASE 141 
#define  OBJECT_DOMAIN 140 
#define  OBJECT_FDW 139 
#define  OBJECT_FOREIGN_SERVER 138 
#define  OBJECT_FUNCTION 137 
#define  OBJECT_LANGUAGE 136 
#define  OBJECT_LARGEOBJECT 135 
#define  OBJECT_PROCEDURE 134 
#define  OBJECT_ROUTINE 133 
#define  OBJECT_SCHEMA 132 
#define  OBJECT_SEQUENCE 131 
#define  OBJECT_TABLE 130 
#define  OBJECT_TABLESPACE 129 
#define  OBJECT_TYPE 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
ExecGrantStmt_oids(InternalGrant *istmt)
{
	switch (istmt->objtype)
	{
		case OBJECT_TABLE:
		case OBJECT_SEQUENCE:
			ExecGrant_Relation(istmt);
			break;
		case OBJECT_DATABASE:
			ExecGrant_Database(istmt);
			break;
		case OBJECT_DOMAIN:
		case OBJECT_TYPE:
			ExecGrant_Type(istmt);
			break;
		case OBJECT_FDW:
			ExecGrant_Fdw(istmt);
			break;
		case OBJECT_FOREIGN_SERVER:
			ExecGrant_ForeignServer(istmt);
			break;
		case OBJECT_FUNCTION:
		case OBJECT_PROCEDURE:
		case OBJECT_ROUTINE:
			ExecGrant_Function(istmt);
			break;
		case OBJECT_LANGUAGE:
			ExecGrant_Language(istmt);
			break;
		case OBJECT_LARGEOBJECT:
			ExecGrant_Largeobject(istmt);
			break;
		case OBJECT_SCHEMA:
			ExecGrant_Namespace(istmt);
			break;
		case OBJECT_TABLESPACE:
			ExecGrant_Tablespace(istmt);
			break;
		default:
			elog(ERROR, "unrecognized GrantStmt.objtype: %d",
				 (int) istmt->objtype);
	}

	/*
	 * Pass the info to event triggers about the just-executed GRANT.  Note
	 * that we prefer to do it after actually executing it, because that gives
	 * the functions a chance to adjust the istmt with privileges actually
	 * granted.
	 */
	if (EventTriggerSupportsObjectType(istmt->objtype))
		EventTriggerCollectGrant(istmt);
}