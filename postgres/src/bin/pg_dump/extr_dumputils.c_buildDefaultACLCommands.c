#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  buildACLCommands (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  fmtId (char const*) ; 
 scalar_t__ strlen (char const*) ; 

bool
buildDefaultACLCommands(const char *type, const char *nspname,
						const char *acls, const char *racls,
						const char *initacls, const char *initracls,
						const char *owner,
						int remoteVersion,
						PQExpBuffer sql)
{
	PQExpBuffer prefix;

	prefix = createPQExpBuffer();

	/*
	 * We incorporate the target role directly into the command, rather than
	 * playing around with SET ROLE or anything like that.  This is so that a
	 * permissions error leads to nothing happening, rather than changing
	 * default privileges for the wrong user.
	 */
	appendPQExpBuffer(prefix, "ALTER DEFAULT PRIVILEGES FOR ROLE %s ",
					  fmtId(owner));
	if (nspname)
		appendPQExpBuffer(prefix, "IN SCHEMA %s ", fmtId(nspname));

	if (strlen(initacls) != 0 || strlen(initracls) != 0)
	{
		appendPQExpBufferStr(sql, "SELECT pg_catalog.binary_upgrade_set_record_init_privs(true);\n");
		if (!buildACLCommands("", NULL, NULL, type,
							  initacls, initracls, owner,
							  prefix->data, remoteVersion, sql))
		{
			destroyPQExpBuffer(prefix);
			return false;
		}
		appendPQExpBufferStr(sql, "SELECT pg_catalog.binary_upgrade_set_record_init_privs(false);\n");
	}

	if (!buildACLCommands("", NULL, NULL, type,
						  acls, racls, owner,
						  prefix->data, remoteVersion, sql))
	{
		destroyPQExpBuffer(prefix);
		return false;
	}

	destroyPQExpBuffer(prefix);

	return true;
}