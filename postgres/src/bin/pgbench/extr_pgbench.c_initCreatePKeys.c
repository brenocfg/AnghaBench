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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 char* PQescapeIdentifier (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  PQfreemem (char*) ; 
 int /*<<< orphan*/  executeStatement (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* index_tablespace ; 
 int lengthof (char const* const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlcpy (char*,char const* const,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
initCreatePKeys(PGconn *con)
{
	static const char *const DDLINDEXes[] = {
		"alter table pgbench_branches add primary key (bid)",
		"alter table pgbench_tellers add primary key (tid)",
		"alter table pgbench_accounts add primary key (aid)"
	};
	int			i;

	fprintf(stderr, "creating primary keys...\n");
	for (i = 0; i < lengthof(DDLINDEXes); i++)
	{
		char		buffer[256];

		strlcpy(buffer, DDLINDEXes[i], sizeof(buffer));

		if (index_tablespace != NULL)
		{
			char	   *escape_tablespace;

			escape_tablespace = PQescapeIdentifier(con, index_tablespace,
												   strlen(index_tablespace));
			snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer),
					 " using index tablespace %s", escape_tablespace);
			PQfreemem(escape_tablespace);
		}

		executeStatement(con, buffer);
	}
}