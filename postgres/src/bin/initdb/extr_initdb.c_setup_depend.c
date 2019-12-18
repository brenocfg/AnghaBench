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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PG_CMD_PUTS (char const* const) ; 

__attribute__((used)) static void
setup_depend(FILE *cmdfd)
{
	const char *const *line;
	static const char *const pg_depend_setup[] = {
		/*
		 * Make PIN entries in pg_depend for all objects made so far in the
		 * tables that the dependency code handles.  This is overkill (the
		 * system doesn't really depend on having every last weird datatype,
		 * for instance) but generating only the minimum required set of
		 * dependencies seems hard.
		 *
		 * Catalogs that are intentionally not scanned here are:
		 *
		 * pg_database: it's a feature, not a bug, that template1 is not
		 * pinned.
		 *
		 * pg_extension: a pinned extension isn't really an extension, hmm?
		 *
		 * pg_tablespace: tablespaces don't participate in the dependency
		 * code, and DropTableSpace() explicitly protects the built-in
		 * tablespaces.
		 *
		 * First delete any already-made entries; PINs override all else, and
		 * must be the only entries for their objects.
		 */
		"DELETE FROM pg_depend;\n\n",
		"VACUUM pg_depend;\n\n",
		"DELETE FROM pg_shdepend;\n\n",
		"VACUUM pg_shdepend;\n\n",

		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_class;\n\n",
		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_proc;\n\n",
		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_type;\n\n",
		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_cast;\n\n",
		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_constraint;\n\n",
		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_conversion;\n\n",
		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_attrdef;\n\n",
		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_language;\n\n",
		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_operator;\n\n",
		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_opclass;\n\n",
		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_opfamily;\n\n",
		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_am;\n\n",
		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_amop;\n\n",
		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_amproc;\n\n",
		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_rewrite;\n\n",
		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_trigger;\n\n",

		/*
		 * restriction here to avoid pinning the public namespace
		 */
		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_namespace "
		"    WHERE nspname LIKE 'pg%';\n\n",

		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_ts_parser;\n\n",
		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_ts_dict;\n\n",
		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_ts_template;\n\n",
		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_ts_config;\n\n",
		"INSERT INTO pg_depend SELECT 0,0,0, tableoid,oid,0, 'p' "
		" FROM pg_collation;\n\n",
		"INSERT INTO pg_shdepend SELECT 0,0,0,0, tableoid,oid, 'p' "
		" FROM pg_authid;\n\n",
		NULL
	};

	for (line = pg_depend_setup; *line != NULL; line++)
		PG_CMD_PUTS(*line);
}