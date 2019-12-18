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
typedef  int /*<<< orphan*/  PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ ,char*,...) ; 

void
buildACLQueries(PQExpBuffer acl_subquery, PQExpBuffer racl_subquery,
				PQExpBuffer init_acl_subquery, PQExpBuffer init_racl_subquery,
				const char *acl_column, const char *acl_owner,
				const char *obj_kind, bool binary_upgrade)
{
	/*
	 * To get the delta from what the permissions were at creation time
	 * (either initdb or CREATE EXTENSION) vs. what they are now, we have to
	 * look at two things:
	 *
	 * What privileges have been added, which we calculate by extracting all
	 * the current privileges (using the set of default privileges for the
	 * object type if current privileges are NULL) and then removing those
	 * which existed at creation time (again, using the set of default
	 * privileges for the object type if there were no creation time
	 * privileges).
	 *
	 * What privileges have been removed, which we calculate by extracting the
	 * privileges as they were at creation time (or the default privileges, as
	 * above), and then removing the current privileges (or the default
	 * privileges, if current privileges are NULL).
	 *
	 * As a good cross-check, both directions of these checks should result in
	 * the empty set if both the current ACL and the initial privs are NULL
	 * (meaning, in practice, that the default ACLs were there at init time
	 * and is what the current privileges are).
	 *
	 * We always perform this delta on all ACLs and expect that by the time
	 * these are run the initial privileges will be in place, even in a binary
	 * upgrade situation (see below).
	 *
	 * Finally, the order in which privileges are in the ACL string (the order
	 * they been GRANT'd in, which the backend maintains) must be preserved to
	 * ensure that GRANTs WITH GRANT OPTION and subsequent GRANTs based on
	 * those are dumped in the correct order.
	 */
	printfPQExpBuffer(acl_subquery,
					  "(SELECT pg_catalog.array_agg(acl ORDER BY row_n) FROM "
					  "(SELECT acl, row_n FROM "
					  "pg_catalog.unnest(coalesce(%s,pg_catalog.acldefault(%s,%s))) "
					  "WITH ORDINALITY AS perm(acl,row_n) "
					  "WHERE NOT EXISTS ( "
					  "SELECT 1 FROM "
					  "pg_catalog.unnest(coalesce(pip.initprivs,pg_catalog.acldefault(%s,%s))) "
					  "AS init(init_acl) WHERE acl = init_acl)) as foo)",
					  acl_column,
					  obj_kind,
					  acl_owner,
					  obj_kind,
					  acl_owner);

	printfPQExpBuffer(racl_subquery,
					  "(SELECT pg_catalog.array_agg(acl ORDER BY row_n) FROM "
					  "(SELECT acl, row_n FROM "
					  "pg_catalog.unnest(coalesce(pip.initprivs,pg_catalog.acldefault(%s,%s))) "
					  "WITH ORDINALITY AS initp(acl,row_n) "
					  "WHERE NOT EXISTS ( "
					  "SELECT 1 FROM "
					  "pg_catalog.unnest(coalesce(%s,pg_catalog.acldefault(%s,%s))) "
					  "AS permp(orig_acl) WHERE acl = orig_acl)) as foo)",
					  obj_kind,
					  acl_owner,
					  acl_column,
					  obj_kind,
					  acl_owner);

	/*
	 * In binary upgrade mode we don't run the extension script but instead
	 * dump out the objects independently and then recreate them.  To preserve
	 * the initial privileges which were set on extension objects, we need to
	 * grab the set of GRANT and REVOKE commands necessary to get from the
	 * default privileges of an object to the initial privileges as recorded
	 * in pg_init_privs.
	 *
	 * These will then be run ahead of the regular ACL commands, which were
	 * calculated using the queries above, inside of a block which sets a flag
	 * to indicate that the backend should record the results of these GRANT
	 * and REVOKE statements into pg_init_privs.  This is how we preserve the
	 * contents of that catalog across binary upgrades.
	 */
	if (binary_upgrade)
	{
		printfPQExpBuffer(init_acl_subquery,
						  "CASE WHEN privtype = 'e' THEN "
						  "(SELECT pg_catalog.array_agg(acl ORDER BY row_n) FROM "
						  "(SELECT acl, row_n FROM pg_catalog.unnest(pip.initprivs) "
						  "WITH ORDINALITY AS initp(acl,row_n) "
						  "WHERE NOT EXISTS ( "
						  "SELECT 1 FROM "
						  "pg_catalog.unnest(pg_catalog.acldefault(%s,%s)) "
						  "AS privm(orig_acl) WHERE acl = orig_acl)) as foo) END",
						  obj_kind,
						  acl_owner);

		printfPQExpBuffer(init_racl_subquery,
						  "CASE WHEN privtype = 'e' THEN "
						  "(SELECT pg_catalog.array_agg(acl) FROM "
						  "(SELECT acl, row_n FROM "
						  "pg_catalog.unnest(pg_catalog.acldefault(%s,%s)) "
						  "WITH ORDINALITY AS privp(acl,row_n) "
						  "WHERE NOT EXISTS ( "
						  "SELECT 1 FROM pg_catalog.unnest(pip.initprivs) "
						  "AS initp(init_acl) WHERE acl = init_acl)) as foo) END",
						  obj_kind,
						  acl_owner);
	}
	else
	{
		printfPQExpBuffer(init_acl_subquery, "NULL");
		printfPQExpBuffer(init_racl_subquery, "NULL");
	}
}