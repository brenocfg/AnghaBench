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

/* Variables and functions */
 int InvalidBackendId ; 
 int atoi (char*) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int
GetTempNamespaceBackendId(Oid namespaceId)
{
	int			result;
	char	   *nspname;

	/* See if the namespace name starts with "pg_temp_" or "pg_toast_temp_" */
	nspname = get_namespace_name(namespaceId);
	if (!nspname)
		return InvalidBackendId;	/* no such namespace? */
	if (strncmp(nspname, "pg_temp_", 8) == 0)
		result = atoi(nspname + 8);
	else if (strncmp(nspname, "pg_toast_temp_", 14) == 0)
		result = atoi(nspname + 14);
	else
		result = InvalidBackendId;
	pfree(nspname);
	return result;
}