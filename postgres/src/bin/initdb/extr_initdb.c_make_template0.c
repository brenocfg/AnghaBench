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
make_template0(FILE *cmdfd)
{
	const char *const *line;
	static const char *const template0_setup[] = {
		"CREATE DATABASE template0 IS_TEMPLATE = true ALLOW_CONNECTIONS = false;\n\n",

		/*
		 * We use the OID of template0 to determine datlastsysoid
		 */
		"UPDATE pg_database SET datlastsysoid = "
		"    (SELECT oid FROM pg_database "
		"    WHERE datname = 'template0');\n\n",

		/*
		 * Explicitly revoke public create-schema and create-temp-table
		 * privileges in template1 and template0; else the latter would be on
		 * by default
		 */
		"REVOKE CREATE,TEMPORARY ON DATABASE template1 FROM public;\n\n",
		"REVOKE CREATE,TEMPORARY ON DATABASE template0 FROM public;\n\n",

		"COMMENT ON DATABASE template0 IS 'unmodifiable empty database';\n\n",

		/*
		 * Finally vacuum to clean up dead rows in pg_database
		 */
		"VACUUM pg_database;\n\n",
		NULL
	};

	for (line = template0_setup; *line; line++)
		PG_CMD_PUTS(*line);
}