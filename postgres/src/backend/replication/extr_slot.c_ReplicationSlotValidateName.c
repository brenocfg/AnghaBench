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

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_NAME ; 
 int /*<<< orphan*/  ERRCODE_NAME_TOO_LONG ; 
 scalar_t__ NAMEDATALEN ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

bool
ReplicationSlotValidateName(const char *name, int elevel)
{
	const char *cp;

	if (strlen(name) == 0)
	{
		ereport(elevel,
				(errcode(ERRCODE_INVALID_NAME),
				 errmsg("replication slot name \"%s\" is too short",
						name)));
		return false;
	}

	if (strlen(name) >= NAMEDATALEN)
	{
		ereport(elevel,
				(errcode(ERRCODE_NAME_TOO_LONG),
				 errmsg("replication slot name \"%s\" is too long",
						name)));
		return false;
	}

	for (cp = name; *cp; cp++)
	{
		if (!((*cp >= 'a' && *cp <= 'z')
			  || (*cp >= '0' && *cp <= '9')
			  || (*cp == '_')))
		{
			ereport(elevel,
					(errcode(ERRCODE_INVALID_NAME),
					 errmsg("replication slot name \"%s\" contains invalid character",
							name),
					 errhint("Replication slot names may only contain lower case letters, numbers, and the underscore character.")));
			return false;
		}
	}
	return true;
}