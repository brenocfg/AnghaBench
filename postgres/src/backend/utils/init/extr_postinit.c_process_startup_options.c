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
struct TYPE_3__ {int /*<<< orphan*/  guc_options; int /*<<< orphan*/ * cmdline_options; } ;
typedef  TYPE_1__ Port ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  int /*<<< orphan*/  GucContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  PGC_BACKEND ; 
 int /*<<< orphan*/  PGC_SU_BACKEND ; 
 int /*<<< orphan*/  PGC_S_CLIENT ; 
 int /*<<< orphan*/  SetConfigOption (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* lfirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lnext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pg_split_opts (char**,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_postgres_switches (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
process_startup_options(Port *port, bool am_superuser)
{
	GucContext	gucctx;
	ListCell   *gucopts;

	gucctx = am_superuser ? PGC_SU_BACKEND : PGC_BACKEND;

	/*
	 * First process any command-line switches that were included in the
	 * startup packet, if we are in a regular backend.
	 */
	if (port->cmdline_options != NULL)
	{
		/*
		 * The maximum possible number of commandline arguments that could
		 * come from port->cmdline_options is (strlen + 1) / 2; see
		 * pg_split_opts().
		 */
		char	  **av;
		int			maxac;
		int			ac;

		maxac = 2 + (strlen(port->cmdline_options) + 1) / 2;

		av = (char **) palloc(maxac * sizeof(char *));
		ac = 0;

		av[ac++] = "postgres";

		pg_split_opts(av, &ac, port->cmdline_options);

		av[ac] = NULL;

		Assert(ac < maxac);

		(void) process_postgres_switches(ac, av, gucctx, NULL);
	}

	/*
	 * Process any additional GUC variable settings passed in startup packet.
	 * These are handled exactly like command-line variables.
	 */
	gucopts = list_head(port->guc_options);
	while (gucopts)
	{
		char	   *name;
		char	   *value;

		name = lfirst(gucopts);
		gucopts = lnext(port->guc_options, gucopts);

		value = lfirst(gucopts);
		gucopts = lnext(port->guc_options, gucopts);

		SetConfigOption(name, value, gucctx, PGC_S_CLIENT);
	}
}