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
typedef  int /*<<< orphan*/  AclMode ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_CONNECT ; 
 int /*<<< orphan*/  ACL_CREATE ; 
 int /*<<< orphan*/  ACL_CREATE_TEMP ; 
 int /*<<< orphan*/  ACL_DELETE ; 
 int /*<<< orphan*/  ACL_EXECUTE ; 
 int /*<<< orphan*/  ACL_INSERT ; 
 int /*<<< orphan*/  ACL_REFERENCES ; 
 int /*<<< orphan*/  ACL_SELECT ; 
 int /*<<< orphan*/  ACL_TRIGGER ; 
 int /*<<< orphan*/  ACL_TRUNCATE ; 
 int /*<<< orphan*/  ACL_UPDATE ; 
 int /*<<< orphan*/  ACL_USAGE ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static AclMode
string_to_privilege(const char *privname)
{
	if (strcmp(privname, "insert") == 0)
		return ACL_INSERT;
	if (strcmp(privname, "select") == 0)
		return ACL_SELECT;
	if (strcmp(privname, "update") == 0)
		return ACL_UPDATE;
	if (strcmp(privname, "delete") == 0)
		return ACL_DELETE;
	if (strcmp(privname, "truncate") == 0)
		return ACL_TRUNCATE;
	if (strcmp(privname, "references") == 0)
		return ACL_REFERENCES;
	if (strcmp(privname, "trigger") == 0)
		return ACL_TRIGGER;
	if (strcmp(privname, "execute") == 0)
		return ACL_EXECUTE;
	if (strcmp(privname, "usage") == 0)
		return ACL_USAGE;
	if (strcmp(privname, "create") == 0)
		return ACL_CREATE;
	if (strcmp(privname, "temporary") == 0)
		return ACL_CREATE_TEMP;
	if (strcmp(privname, "temp") == 0)
		return ACL_CREATE_TEMP;
	if (strcmp(privname, "connect") == 0)
		return ACL_CONNECT;
	if (strcmp(privname, "rule") == 0)
		return 0;				/* ignore old RULE privileges */
	ereport(ERROR,
			(errcode(ERRCODE_SYNTAX_ERROR),
			 errmsg("unrecognized privilege type \"%s\"", privname)));
	return 0;					/* appease compiler */
}