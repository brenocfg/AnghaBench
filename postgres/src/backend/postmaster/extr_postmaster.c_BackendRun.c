#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  user_name; int /*<<< orphan*/  database_name; } ;
typedef  TYPE_1__ Port ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DEBUG3 ; 
 int /*<<< orphan*/  ExtraOptions ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostgresMain (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*,...) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  pg_split_opts (char**,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  progname ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
BackendRun(Port *port)
{
	char	  **av;
	int			maxac;
	int			ac;
	int			i;

	/*
	 * Now, build the argv vector that will be given to PostgresMain.
	 *
	 * The maximum possible number of commandline arguments that could come
	 * from ExtraOptions is (strlen(ExtraOptions) + 1) / 2; see
	 * pg_split_opts().
	 */
	maxac = 2;					/* for fixed args supplied below */
	maxac += (strlen(ExtraOptions) + 1) / 2;

	av = (char **) MemoryContextAlloc(TopMemoryContext,
									  maxac * sizeof(char *));
	ac = 0;

	av[ac++] = "postgres";

	/*
	 * Pass any backend switches specified with -o on the postmaster's own
	 * command line.  We assume these are secure.
	 */
	pg_split_opts(av, &ac, ExtraOptions);

	av[ac] = NULL;

	Assert(ac < maxac);

	/*
	 * Debug: print arguments being passed to backend
	 */
	ereport(DEBUG3,
			(errmsg_internal("%s child[%d]: starting with (",
							 progname, (int) getpid())));
	for (i = 0; i < ac; ++i)
		ereport(DEBUG3,
				(errmsg_internal("\t%s", av[i])));
	ereport(DEBUG3,
			(errmsg_internal(")")));

	/*
	 * Make sure we aren't in PostmasterContext anymore.  (We can't delete it
	 * just yet, though, because InitPostgres will need the HBA data.)
	 */
	MemoryContextSwitchTo(TopMemoryContext);

	PostgresMain(ac, av, port->database_name, port->user_name);
}