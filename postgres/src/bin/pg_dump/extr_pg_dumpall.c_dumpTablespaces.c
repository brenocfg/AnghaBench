#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  OPF ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,char*,...) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  appendStringLiteralConn (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atooid (char*) ; 
 int /*<<< orphan*/  buildACLCommands (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,char*,char*,char*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  buildShSecLabels (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,char*,TYPE_1__*) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/ * executeQuery (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  exit_nicely (int) ; 
 char* fmtId (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  no_comments ; 
 int /*<<< orphan*/  no_security_labels ; 
 int /*<<< orphan*/  pg_log_error (char*,char*,char*) ; 
 char* pg_strdup (char*) ; 
 int server_version ; 
 int /*<<< orphan*/  skip_acls ; 

__attribute__((used)) static void
dumpTablespaces(PGconn *conn)
{
	PGresult   *res;
	int			i;

	/*
	 * Get all tablespaces except built-in ones (which we assume are named
	 * pg_xxx)
	 *
	 * For the tablespace ACLs, as of 9.6, we extract both the positive (as
	 * spcacl) and negative (as rspcacl) ACLs, relative to the default ACL for
	 * tablespaces, which are then passed to buildACLCommands() below.
	 *
	 * See buildACLQueries() and buildACLCommands().
	 *
	 * The order in which privileges are in the ACL string (the order they
	 * have been GRANT'd in, which the backend maintains) must be preserved to
	 * ensure that GRANTs WITH GRANT OPTION and subsequent GRANTs based on
	 * those are dumped in the correct order.
	 *
	 * Note that we do not support initial privileges (pg_init_privs) on
	 * tablespaces, so this logic cannot make use of buildACLQueries().
	 */
	if (server_version >= 90600)
		res = executeQuery(conn, "SELECT oid, spcname, "
						   "pg_catalog.pg_get_userbyid(spcowner) AS spcowner, "
						   "pg_catalog.pg_tablespace_location(oid), "
						   "(SELECT array_agg(acl ORDER BY row_n) FROM "
						   "  (SELECT acl, row_n FROM "
						   "     unnest(coalesce(spcacl,acldefault('t',spcowner))) "
						   "     WITH ORDINALITY AS perm(acl,row_n) "
						   "   WHERE NOT EXISTS ( "
						   "     SELECT 1 "
						   "     FROM unnest(acldefault('t',spcowner)) "
						   "       AS init(init_acl) "
						   "     WHERE acl = init_acl)) AS spcacls) "
						   " AS spcacl, "
						   "(SELECT array_agg(acl ORDER BY row_n) FROM "
						   "  (SELECT acl, row_n FROM "
						   "     unnest(acldefault('t',spcowner)) "
						   "     WITH ORDINALITY AS initp(acl,row_n) "
						   "   WHERE NOT EXISTS ( "
						   "     SELECT 1 "
						   "     FROM unnest(coalesce(spcacl,acldefault('t',spcowner))) "
						   "       AS permp(orig_acl) "
						   "     WHERE acl = orig_acl)) AS rspcacls) "
						   " AS rspcacl, "
						   "array_to_string(spcoptions, ', '),"
						   "pg_catalog.shobj_description(oid, 'pg_tablespace') "
						   "FROM pg_catalog.pg_tablespace "
						   "WHERE spcname !~ '^pg_' "
						   "ORDER BY 1");
	else if (server_version >= 90200)
		res = executeQuery(conn, "SELECT oid, spcname, "
						   "pg_catalog.pg_get_userbyid(spcowner) AS spcowner, "
						   "pg_catalog.pg_tablespace_location(oid), "
						   "spcacl, '' as rspcacl, "
						   "array_to_string(spcoptions, ', '),"
						   "pg_catalog.shobj_description(oid, 'pg_tablespace') "
						   "FROM pg_catalog.pg_tablespace "
						   "WHERE spcname !~ '^pg_' "
						   "ORDER BY 1");
	else if (server_version >= 90000)
		res = executeQuery(conn, "SELECT oid, spcname, "
						   "pg_catalog.pg_get_userbyid(spcowner) AS spcowner, "
						   "spclocation, spcacl, '' as rspcacl, "
						   "array_to_string(spcoptions, ', '),"
						   "pg_catalog.shobj_description(oid, 'pg_tablespace') "
						   "FROM pg_catalog.pg_tablespace "
						   "WHERE spcname !~ '^pg_' "
						   "ORDER BY 1");
	else if (server_version >= 80200)
		res = executeQuery(conn, "SELECT oid, spcname, "
						   "pg_catalog.pg_get_userbyid(spcowner) AS spcowner, "
						   "spclocation, spcacl, '' as rspcacl, null, "
						   "pg_catalog.shobj_description(oid, 'pg_tablespace') "
						   "FROM pg_catalog.pg_tablespace "
						   "WHERE spcname !~ '^pg_' "
						   "ORDER BY 1");
	else
		res = executeQuery(conn, "SELECT oid, spcname, "
						   "pg_catalog.pg_get_userbyid(spcowner) AS spcowner, "
						   "spclocation, spcacl, '' as rspcacl, "
						   "null, null "
						   "FROM pg_catalog.pg_tablespace "
						   "WHERE spcname !~ '^pg_' "
						   "ORDER BY 1");

	if (PQntuples(res) > 0)
		fprintf(OPF, "--\n-- Tablespaces\n--\n\n");

	for (i = 0; i < PQntuples(res); i++)
	{
		PQExpBuffer buf = createPQExpBuffer();
		Oid			spcoid = atooid(PQgetvalue(res, i, 0));
		char	   *spcname = PQgetvalue(res, i, 1);
		char	   *spcowner = PQgetvalue(res, i, 2);
		char	   *spclocation = PQgetvalue(res, i, 3);
		char	   *spcacl = PQgetvalue(res, i, 4);
		char	   *rspcacl = PQgetvalue(res, i, 5);
		char	   *spcoptions = PQgetvalue(res, i, 6);
		char	   *spccomment = PQgetvalue(res, i, 7);
		char	   *fspcname;

		/* needed for buildACLCommands() */
		fspcname = pg_strdup(fmtId(spcname));

		appendPQExpBuffer(buf, "CREATE TABLESPACE %s", fspcname);
		appendPQExpBuffer(buf, " OWNER %s", fmtId(spcowner));

		appendPQExpBufferStr(buf, " LOCATION ");
		appendStringLiteralConn(buf, spclocation, conn);
		appendPQExpBufferStr(buf, ";\n");

		if (spcoptions && spcoptions[0] != '\0')
			appendPQExpBuffer(buf, "ALTER TABLESPACE %s SET (%s);\n",
							  fspcname, spcoptions);

		if (!skip_acls &&
			!buildACLCommands(fspcname, NULL, NULL, "TABLESPACE",
							  spcacl, rspcacl,
							  spcowner, "", server_version, buf))
		{
			pg_log_error("could not parse ACL list (%s) for tablespace \"%s\"",
						 spcacl, spcname);
			PQfinish(conn);
			exit_nicely(1);
		}

		if (!no_comments && spccomment && spccomment[0] != '\0')
		{
			appendPQExpBuffer(buf, "COMMENT ON TABLESPACE %s IS ", fspcname);
			appendStringLiteralConn(buf, spccomment, conn);
			appendPQExpBufferStr(buf, ";\n");
		}

		if (!no_security_labels && server_version >= 90200)
			buildShSecLabels(conn, "pg_tablespace", spcoid,
							 "TABLESPACE", spcname,
							 buf);

		fprintf(OPF, "%s", buf->data);

		free(fspcname);
		destroyPQExpBuffer(buf);
	}

	PQclear(res);
	fprintf(OPF, "\n\n");
}