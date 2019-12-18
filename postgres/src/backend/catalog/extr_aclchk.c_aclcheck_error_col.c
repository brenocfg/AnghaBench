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
typedef  int /*<<< orphan*/  ObjectType ;
typedef  int AclResult ;

/* Variables and functions */
#define  ACLCHECK_NOT_OWNER 130 
#define  ACLCHECK_NO_PRIV 129 
#define  ACLCHECK_OK 128 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  aclcheck_error (int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,char const*) ; 

void
aclcheck_error_col(AclResult aclerr, ObjectType objtype,
				   const char *objectname, const char *colname)
{
	switch (aclerr)
	{
		case ACLCHECK_OK:
			/* no error, so return to caller */
			break;
		case ACLCHECK_NO_PRIV:
			ereport(ERROR,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("permission denied for column \"%s\" of relation \"%s\"",
							colname, objectname)));
			break;
		case ACLCHECK_NOT_OWNER:
			/* relation msg is OK since columns don't have separate owners */
			aclcheck_error(aclerr, objtype, objectname);
			break;
		default:
			elog(ERROR, "unrecognized AclResult: %d", (int) aclerr);
			break;
	}
}