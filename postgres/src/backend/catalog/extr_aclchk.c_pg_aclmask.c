#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Oid ;
typedef  int ObjectType ;
typedef  int /*<<< orphan*/  AttrNumber ;
typedef  int AclMode ;
typedef  int /*<<< orphan*/  AclMaskHow ;

/* Variables and functions */
 int ACL_NO_RIGHTS ; 
 int /*<<< orphan*/  ERROR ; 
#define  OBJECT_COLUMN 141 
#define  OBJECT_DATABASE 140 
#define  OBJECT_EVENT_TRIGGER 139 
#define  OBJECT_FDW 138 
#define  OBJECT_FOREIGN_SERVER 137 
#define  OBJECT_FUNCTION 136 
#define  OBJECT_LANGUAGE 135 
#define  OBJECT_LARGEOBJECT 134 
#define  OBJECT_SCHEMA 133 
#define  OBJECT_SEQUENCE 132 
#define  OBJECT_STATISTIC_EXT 131 
#define  OBJECT_TABLE 130 
#define  OBJECT_TABLESPACE 129 
#define  OBJECT_TYPE 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int pg_attribute_aclmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int pg_class_aclmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int pg_database_aclmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int pg_foreign_data_wrapper_aclmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int pg_foreign_server_aclmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int pg_language_aclmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int pg_largeobject_aclmask_snapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pg_namespace_aclmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int pg_proc_aclmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int pg_tablespace_aclmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int pg_type_aclmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static AclMode
pg_aclmask(ObjectType objtype, Oid table_oid, AttrNumber attnum, Oid roleid,
		   AclMode mask, AclMaskHow how)
{
	switch (objtype)
	{
		case OBJECT_COLUMN:
			return
				pg_class_aclmask(table_oid, roleid, mask, how) |
				pg_attribute_aclmask(table_oid, attnum, roleid, mask, how);
		case OBJECT_TABLE:
		case OBJECT_SEQUENCE:
			return pg_class_aclmask(table_oid, roleid, mask, how);
		case OBJECT_DATABASE:
			return pg_database_aclmask(table_oid, roleid, mask, how);
		case OBJECT_FUNCTION:
			return pg_proc_aclmask(table_oid, roleid, mask, how);
		case OBJECT_LANGUAGE:
			return pg_language_aclmask(table_oid, roleid, mask, how);
		case OBJECT_LARGEOBJECT:
			return pg_largeobject_aclmask_snapshot(table_oid, roleid,
												   mask, how, NULL);
		case OBJECT_SCHEMA:
			return pg_namespace_aclmask(table_oid, roleid, mask, how);
		case OBJECT_STATISTIC_EXT:
			elog(ERROR, "grantable rights not supported for statistics objects");
			/* not reached, but keep compiler quiet */
			return ACL_NO_RIGHTS;
		case OBJECT_TABLESPACE:
			return pg_tablespace_aclmask(table_oid, roleid, mask, how);
		case OBJECT_FDW:
			return pg_foreign_data_wrapper_aclmask(table_oid, roleid, mask, how);
		case OBJECT_FOREIGN_SERVER:
			return pg_foreign_server_aclmask(table_oid, roleid, mask, how);
		case OBJECT_EVENT_TRIGGER:
			elog(ERROR, "grantable rights not supported for event triggers");
			/* not reached, but keep compiler quiet */
			return ACL_NO_RIGHTS;
		case OBJECT_TYPE:
			return pg_type_aclmask(table_oid, roleid, mask, how);
		default:
			elog(ERROR, "unrecognized objtype: %d",
				 (int) objtype);
			/* not reached, but keep compiler quiet */
			return ACL_NO_RIGHTS;
	}
}