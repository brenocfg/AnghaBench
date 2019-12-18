#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ len; char const* data; } ;
typedef  TYPE_1__* PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,char const*,...) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 char* fmtId (char const*) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  parseAclItem (char*,char const*,char const*,char const*,int,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  parsePGArray (char const*,char***,int*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_1__*,char*,char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

bool
buildACLCommands(const char *name, const char *subname, const char *nspname,
				 const char *type, const char *acls, const char *racls,
				 const char *owner, const char *prefix, int remoteVersion,
				 PQExpBuffer sql)
{
	bool		ok = true;
	char	  **aclitems = NULL;
	char	  **raclitems = NULL;
	int			naclitems = 0;
	int			nraclitems = 0;
	int			i;
	PQExpBuffer grantee,
				grantor,
				privs,
				privswgo;
	PQExpBuffer firstsql,
				secondsql;
	bool		found_owner_privs = false;

	if (strlen(acls) == 0 && strlen(racls) == 0)
		return true;			/* object has default permissions */

	/* treat empty-string owner same as NULL */
	if (owner && *owner == '\0')
		owner = NULL;

	if (strlen(acls) != 0)
	{
		if (!parsePGArray(acls, &aclitems, &naclitems))
		{
			if (aclitems)
				free(aclitems);
			return false;
		}
	}

	if (strlen(racls) != 0)
	{
		if (!parsePGArray(racls, &raclitems, &nraclitems))
		{
			if (aclitems)
				free(aclitems);
			if (raclitems)
				free(raclitems);
			return false;
		}
	}

	grantee = createPQExpBuffer();
	grantor = createPQExpBuffer();
	privs = createPQExpBuffer();
	privswgo = createPQExpBuffer();

	/*
	 * At the end, these two will be pasted together to form the result.
	 *
	 * For older systems we use these to ensure that the owner privileges go
	 * before the other ones, as a GRANT could create the default entry for
	 * the object, which generally includes all rights for the owner. In more
	 * recent versions we normally handle this because the owner rights come
	 * first in the ACLs, but older versions might have them after the PUBLIC
	 * privileges.
	 *
	 * For 9.6 and later systems, much of this changes.  With 9.6, we check
	 * the default privileges for the objects at dump time and create two sets
	 * of ACLs- "racls" which are the ACLs to REVOKE from the object (as the
	 * object may have initial privileges on it, along with any default ACLs
	 * which are not part of the current set of privileges), and regular
	 * "acls", which are the ACLs to GRANT to the object.  We handle the
	 * REVOKEs first, followed by the GRANTs.
	 */
	firstsql = createPQExpBuffer();
	secondsql = createPQExpBuffer();

	/*
	 * For pre-9.6 systems, we always start with REVOKE ALL FROM PUBLIC, as we
	 * don't wish to make any assumptions about what the default ACLs are, and
	 * we do not collect them during the dump phase (and racls will always be
	 * the empty set, see above).
	 *
	 * For 9.6 and later, if any revoke ACLs have been provided, then include
	 * them in 'firstsql'.
	 *
	 * Revoke ACLs happen when an object starts out life with a set of
	 * privileges (eg: GRANT SELECT ON pg_class TO PUBLIC;) and the user has
	 * decided to revoke those rights.  Since those objects come into being
	 * with those default privileges, we have to revoke them to match what the
	 * current state of affairs is.  Note that we only started explicitly
	 * tracking such initial rights in 9.6, and prior to that all initial
	 * rights are actually handled by the simple 'REVOKE ALL .. FROM PUBLIC'
	 * case, for initdb-created objects.  Prior to 9.6, we didn't handle
	 * extensions correctly, but we do now by tracking their initial
	 * privileges, in the same way we track initdb initial privileges, see
	 * pg_init_privs.
	 */
	if (remoteVersion < 90600)
	{
		Assert(nraclitems == 0);

		appendPQExpBuffer(firstsql, "%sREVOKE ALL", prefix);
		if (subname)
			appendPQExpBuffer(firstsql, "(%s)", subname);
		appendPQExpBuffer(firstsql, " ON %s ", type);
		if (nspname && *nspname)
			appendPQExpBuffer(firstsql, "%s.", fmtId(nspname));
		appendPQExpBuffer(firstsql, "%s FROM PUBLIC;\n", name);
	}
	else
	{
		/* Scan individual REVOKE ACL items */
		for (i = 0; i < nraclitems; i++)
		{
			if (!parseAclItem(raclitems[i], type, name, subname, remoteVersion,
							  grantee, grantor, privs, privswgo))
			{
				ok = false;
				break;
			}

			if (privs->len > 0 || privswgo->len > 0)
			{
				if (privs->len > 0)
				{
					appendPQExpBuffer(firstsql, "%sREVOKE %s ON %s ",
									  prefix, privs->data, type);
					if (nspname && *nspname)
						appendPQExpBuffer(firstsql, "%s.", fmtId(nspname));
					appendPQExpBuffer(firstsql, "%s FROM ", name);
					if (grantee->len == 0)
						appendPQExpBufferStr(firstsql, "PUBLIC;\n");
					else if (strncmp(grantee->data, "group ",
									 strlen("group ")) == 0)
						appendPQExpBuffer(firstsql, "GROUP %s;\n",
										  fmtId(grantee->data + strlen("group ")));
					else
						appendPQExpBuffer(firstsql, "%s;\n",
										  fmtId(grantee->data));
				}
				if (privswgo->len > 0)
				{
					appendPQExpBuffer(firstsql,
									  "%sREVOKE GRANT OPTION FOR %s ON %s ",
									  prefix, privswgo->data, type);
					if (nspname && *nspname)
						appendPQExpBuffer(firstsql, "%s.", fmtId(nspname));
					appendPQExpBuffer(firstsql, "%s FROM ", name);
					if (grantee->len == 0)
						appendPQExpBufferStr(firstsql, "PUBLIC");
					else if (strncmp(grantee->data, "group ",
									 strlen("group ")) == 0)
						appendPQExpBuffer(firstsql, "GROUP %s",
										  fmtId(grantee->data + strlen("group ")));
					else
						appendPQExpBufferStr(firstsql, fmtId(grantee->data));
				}
			}
		}
	}

	/*
	 * We still need some hacking though to cover the case where new default
	 * public privileges are added in new versions: the REVOKE ALL will revoke
	 * them, leading to behavior different from what the old version had,
	 * which is generally not what's wanted.  So add back default privs if the
	 * source database is too old to have had that particular priv.
	 */
	if (remoteVersion < 80200 && strcmp(type, "DATABASE") == 0)
	{
		/* database CONNECT priv didn't exist before 8.2 */
		appendPQExpBuffer(firstsql, "%sGRANT CONNECT ON %s %s TO PUBLIC;\n",
						  prefix, type, name);
	}

	/* Scan individual ACL items */
	for (i = 0; i < naclitems; i++)
	{
		if (!parseAclItem(aclitems[i], type, name, subname, remoteVersion,
						  grantee, grantor, privs, privswgo))
		{
			ok = false;
			break;
		}

		if (grantor->len == 0 && owner)
			printfPQExpBuffer(grantor, "%s", owner);

		if (privs->len > 0 || privswgo->len > 0)
		{
			/*
			 * Prior to 9.6, we had to handle owner privileges in a special
			 * manner by first REVOKE'ing the rights and then GRANT'ing them
			 * after.  With 9.6 and above, what we need to REVOKE and what we
			 * need to GRANT is figured out when we dump and stashed into
			 * "racls" and "acls", respectively.  See above.
			 */
			if (remoteVersion < 90600 && owner
				&& strcmp(grantee->data, owner) == 0
				&& strcmp(grantor->data, owner) == 0)
			{
				found_owner_privs = true;

				/*
				 * For the owner, the default privilege level is ALL WITH
				 * GRANT OPTION.
				 */
				if (strcmp(privswgo->data, "ALL") != 0)
				{
					appendPQExpBuffer(firstsql, "%sREVOKE ALL", prefix);
					if (subname)
						appendPQExpBuffer(firstsql, "(%s)", subname);
					appendPQExpBuffer(firstsql, " ON %s ", type);
					if (nspname && *nspname)
						appendPQExpBuffer(firstsql, "%s.", fmtId(nspname));
					appendPQExpBuffer(firstsql, "%s FROM %s;\n",
									  name, fmtId(grantee->data));
					if (privs->len > 0)
					{
						appendPQExpBuffer(firstsql,
										  "%sGRANT %s ON %s ",
										  prefix, privs->data, type);
						if (nspname && *nspname)
							appendPQExpBuffer(firstsql, "%s.", fmtId(nspname));
						appendPQExpBuffer(firstsql,
										  "%s TO %s;\n",
										  name, fmtId(grantee->data));
					}
					if (privswgo->len > 0)
					{
						appendPQExpBuffer(firstsql,
										  "%sGRANT %s ON %s ",
										  prefix, privswgo->data, type);
						if (nspname && *nspname)
							appendPQExpBuffer(firstsql, "%s.", fmtId(nspname));
						appendPQExpBuffer(firstsql,
										  "%s TO %s WITH GRANT OPTION;\n",
										  name, fmtId(grantee->data));
					}
				}
			}
			else
			{
				/*
				 * For systems prior to 9.6, we can assume we are starting
				 * from no privs at this point.
				 *
				 * For 9.6 and above, at this point we have issued REVOKE
				 * statements for all initial and default privileges which are
				 * no longer present on the object (as they were passed in as
				 * 'racls') and we can simply GRANT the rights which are in
				 * 'acls'.
				 */
				if (grantor->len > 0
					&& (!owner || strcmp(owner, grantor->data) != 0))
					appendPQExpBuffer(secondsql, "SET SESSION AUTHORIZATION %s;\n",
									  fmtId(grantor->data));

				if (privs->len > 0)
				{
					appendPQExpBuffer(secondsql, "%sGRANT %s ON %s ",
									  prefix, privs->data, type);
					if (nspname && *nspname)
						appendPQExpBuffer(secondsql, "%s.", fmtId(nspname));
					appendPQExpBuffer(secondsql, "%s TO ", name);
					if (grantee->len == 0)
						appendPQExpBufferStr(secondsql, "PUBLIC;\n");
					else if (strncmp(grantee->data, "group ",
									 strlen("group ")) == 0)
						appendPQExpBuffer(secondsql, "GROUP %s;\n",
										  fmtId(grantee->data + strlen("group ")));
					else
						appendPQExpBuffer(secondsql, "%s;\n", fmtId(grantee->data));
				}
				if (privswgo->len > 0)
				{
					appendPQExpBuffer(secondsql, "%sGRANT %s ON %s ",
									  prefix, privswgo->data, type);
					if (nspname && *nspname)
						appendPQExpBuffer(secondsql, "%s.", fmtId(nspname));
					appendPQExpBuffer(secondsql, "%s TO ", name);
					if (grantee->len == 0)
						appendPQExpBufferStr(secondsql, "PUBLIC");
					else if (strncmp(grantee->data, "group ",
									 strlen("group ")) == 0)
						appendPQExpBuffer(secondsql, "GROUP %s",
										  fmtId(grantee->data + strlen("group ")));
					else
						appendPQExpBufferStr(secondsql, fmtId(grantee->data));
					appendPQExpBufferStr(secondsql, " WITH GRANT OPTION;\n");
				}

				if (grantor->len > 0
					&& (!owner || strcmp(owner, grantor->data) != 0))
					appendPQExpBufferStr(secondsql, "RESET SESSION AUTHORIZATION;\n");
			}
		}
	}

	/*
	 * For systems prior to 9.6, if we didn't find any owner privs, the owner
	 * must have revoked 'em all.
	 *
	 * For 9.6 and above, we handle this through the 'racls'.  See above.
	 */
	if (remoteVersion < 90600 && !found_owner_privs && owner)
	{
		appendPQExpBuffer(firstsql, "%sREVOKE ALL", prefix);
		if (subname)
			appendPQExpBuffer(firstsql, "(%s)", subname);
		appendPQExpBuffer(firstsql, " ON %s ", type);
		if (nspname && *nspname)
			appendPQExpBuffer(firstsql, "%s.", fmtId(nspname));
		appendPQExpBuffer(firstsql, "%s FROM %s;\n",
						  name, fmtId(owner));
	}

	destroyPQExpBuffer(grantee);
	destroyPQExpBuffer(grantor);
	destroyPQExpBuffer(privs);
	destroyPQExpBuffer(privswgo);

	appendPQExpBuffer(sql, "%s%s", firstsql->data, secondsql->data);
	destroyPQExpBuffer(firstsql);
	destroyPQExpBuffer(secondsql);

	if (aclitems)
		free(aclitems);

	if (raclitems)
		free(raclitems);

	return ok;
}