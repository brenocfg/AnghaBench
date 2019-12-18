#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  output_path ;
struct TYPE_7__ {TYPE_1__* dbs; } ;
struct TYPE_10__ {TYPE_2__ dbarr; int /*<<< orphan*/  major_version; } ;
struct TYPE_9__ {int num_libraries; TYPE_3__* libraries; } ;
struct TYPE_8__ {char* name; size_t dbnum; } ;
struct TYPE_6__ {char* db_name; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  LibraryInfo ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int GET_MAJOR_VERSION (int /*<<< orphan*/ ) ; 
 int MAXPGPATH ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PG_REPORT ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char* PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQescapeStringConn (int /*<<< orphan*/ *,char*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  check_ok () ; 
 int /*<<< orphan*/ * connectToServer (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_priv (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  library_name_compare ; 
 int /*<<< orphan*/  new_cluster ; 
 TYPE_5__ old_cluster ; 
 TYPE_4__ os_info ; 
 int /*<<< orphan*/  pg_fatal (char*,char*,...) ; 
 int /*<<< orphan*/  pg_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  prep_status (char*) ; 
 int /*<<< orphan*/  qsort (void*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

void
check_loadable_libraries(void)
{
	PGconn	   *conn = connectToServer(&new_cluster, "template1");
	int			libnum;
	int			was_load_failure = false;
	FILE	   *script = NULL;
	bool		found = false;
	char		output_path[MAXPGPATH];

	prep_status("Checking for presence of required libraries");

	snprintf(output_path, sizeof(output_path), "loadable_libraries.txt");

	/*
	 * Now we want to sort the library names into order.  This avoids multiple
	 * probes of the same library, and ensures that libraries are probed in a
	 * consistent order, which is important for reproducible behavior if one
	 * library depends on another.
	 */
	qsort((void *) os_info.libraries, os_info.num_libraries,
		  sizeof(LibraryInfo), library_name_compare);

	for (libnum = 0; libnum < os_info.num_libraries; libnum++)
	{
		char	   *lib = os_info.libraries[libnum].name;
		int			llen = strlen(lib);
		char		cmd[7 + 2 * MAXPGPATH + 1];
		PGresult   *res;

		/* Did the library name change?  Probe it. */
		if (libnum == 0 || strcmp(lib, os_info.libraries[libnum - 1].name) != 0)
		{
			/*
			 * In Postgres 9.0, Python 3 support was added, and to do that, a
			 * plpython2u language was created with library name plpython2.so
			 * as a symbolic link to plpython.so.  In Postgres 9.1, only the
			 * plpython2.so library was created, and both plpythonu and
			 * plpython2u pointing to it.  For this reason, any reference to
			 * library name "plpython" in an old PG <= 9.1 cluster must look
			 * for "plpython2" in the new cluster.
			 *
			 * For this case, we could check pg_pltemplate, but that only
			 * works for languages, and does not help with function shared
			 * objects, so we just do a general fix.
			 */
			if (GET_MAJOR_VERSION(old_cluster.major_version) < 901 &&
				strcmp(lib, "$libdir/plpython") == 0)
			{
				lib = "$libdir/plpython2";
				llen = strlen(lib);
			}

			strcpy(cmd, "LOAD '");
			PQescapeStringConn(conn, cmd + strlen(cmd), lib, llen, NULL);
			strcat(cmd, "'");

			res = PQexec(conn, cmd);

			if (PQresultStatus(res) != PGRES_COMMAND_OK)
			{
				found = true;
				was_load_failure = true;

				if (script == NULL && (script = fopen_priv(output_path, "w")) == NULL)
					pg_fatal("could not open file \"%s\": %s\n",
							 output_path, strerror(errno));
				fprintf(script, _("could not load library \"%s\": %s"),
						lib,
						PQerrorMessage(conn));
			}
			else
				was_load_failure = false;

			PQclear(res);
		}

		if (was_load_failure)
			fprintf(script, _("In database: %s\n"),
					old_cluster.dbarr.dbs[os_info.libraries[libnum].dbnum].db_name);
	}

	PQfinish(conn);

	if (found)
	{
		fclose(script);
		pg_log(PG_REPORT, "fatal\n");
		pg_fatal("Your installation references loadable libraries that are missing from the\n"
				 "new installation.  You can add these libraries to the new installation,\n"
				 "or remove the functions using them from the old installation.  A list of\n"
				 "problem libraries is in the file:\n"
				 "    %s\n\n", output_path);
	}
	else
		check_ok();
}