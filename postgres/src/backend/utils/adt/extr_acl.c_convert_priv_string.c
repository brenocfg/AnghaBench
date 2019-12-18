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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  AclMode ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_CONNECT ; 
 int /*<<< orphan*/  ACL_CREATE ; 
 int /*<<< orphan*/  ACL_CREATE_TEMP ; 
 int /*<<< orphan*/  ACL_DELETE ; 
 int /*<<< orphan*/  ACL_EXECUTE ; 
 int /*<<< orphan*/  ACL_INSERT ; 
 int /*<<< orphan*/  ACL_NO_RIGHTS ; 
 int /*<<< orphan*/  ACL_REFERENCES ; 
 int /*<<< orphan*/  ACL_SELECT ; 
 int /*<<< orphan*/  ACL_TRIGGER ; 
 int /*<<< orphan*/  ACL_TRUNCATE ; 
 int /*<<< orphan*/  ACL_UPDATE ; 
 int /*<<< orphan*/  ACL_USAGE ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ pg_strcasecmp (char*,char*) ; 
 char* text_to_cstring (int /*<<< orphan*/ *) ; 

__attribute__((used)) static AclMode
convert_priv_string(text *priv_type_text)
{
	char	   *priv_type = text_to_cstring(priv_type_text);

	if (pg_strcasecmp(priv_type, "SELECT") == 0)
		return ACL_SELECT;
	if (pg_strcasecmp(priv_type, "INSERT") == 0)
		return ACL_INSERT;
	if (pg_strcasecmp(priv_type, "UPDATE") == 0)
		return ACL_UPDATE;
	if (pg_strcasecmp(priv_type, "DELETE") == 0)
		return ACL_DELETE;
	if (pg_strcasecmp(priv_type, "TRUNCATE") == 0)
		return ACL_TRUNCATE;
	if (pg_strcasecmp(priv_type, "REFERENCES") == 0)
		return ACL_REFERENCES;
	if (pg_strcasecmp(priv_type, "TRIGGER") == 0)
		return ACL_TRIGGER;
	if (pg_strcasecmp(priv_type, "EXECUTE") == 0)
		return ACL_EXECUTE;
	if (pg_strcasecmp(priv_type, "USAGE") == 0)
		return ACL_USAGE;
	if (pg_strcasecmp(priv_type, "CREATE") == 0)
		return ACL_CREATE;
	if (pg_strcasecmp(priv_type, "TEMP") == 0)
		return ACL_CREATE_TEMP;
	if (pg_strcasecmp(priv_type, "TEMPORARY") == 0)
		return ACL_CREATE_TEMP;
	if (pg_strcasecmp(priv_type, "CONNECT") == 0)
		return ACL_CONNECT;
	if (pg_strcasecmp(priv_type, "RULE") == 0)
		return 0;				/* ignore old RULE privileges */

	ereport(ERROR,
			(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
			 errmsg("unrecognized privilege type: \"%s\"", priv_type)));
	return ACL_NO_RIGHTS;		/* keep compiler quiet */
}