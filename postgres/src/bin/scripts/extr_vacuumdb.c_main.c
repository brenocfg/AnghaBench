#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int and_analyze; int analyze_only; int freeze; int full; int verbose; int disable_page_skipping; int skip_locked; void* min_mxid_age; void* min_xid_age; } ;
typedef  TYPE_1__ vacuumingOptions ;
typedef  int /*<<< orphan*/  vacopts ;
struct option {char* member_0; char member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  const member_1; } ;
typedef  enum trivalue { ____Placeholder_trivalue } trivalue ;
struct TYPE_9__ {int /*<<< orphan*/ * head; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ SimpleStringList ;

/* Variables and functions */
 int ANALYZE_NO_STAGE ; 
 int ANALYZE_NUM_STAGES ; 
 int /*<<< orphan*/  PG_TEXTDOMAIN (char*) ; 
 int TRI_DEFAULT ; 
 int TRI_NO ; 
 int TRI_YES ; 
 char* _ (char*) ; 
 void* atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 char* get_progname (char*) ; 
 char* get_user_name_or_exit (char const*) ; 
 char* getenv (char*) ; 
 int getopt_long (int,char**,char*,struct option*,int*) ; 
 int /*<<< orphan*/  handle_help_version_opts (int,char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  help ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
#define  no_argument 129 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int /*<<< orphan*/  pg_logging_init (char*) ; 
 void* pg_strdup (int /*<<< orphan*/ ) ; 
#define  required_argument 128 
 int /*<<< orphan*/  set_pglocale_pgservice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_cancel_handler () ; 
 int /*<<< orphan*/  simple_string_list_append (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vacuum_all_databases (TYPE_1__*,int,char const*,char*,char*,char*,int,int,char const*,int,int) ; 
 int /*<<< orphan*/  vacuum_one_database (char const*,TYPE_1__*,int,TYPE_2__*,char*,char*,char*,int,int,char const*,int,int) ; 

int
main(int argc, char *argv[])
{
	static struct option long_options[] = {
		{"host", required_argument, NULL, 'h'},
		{"port", required_argument, NULL, 'p'},
		{"username", required_argument, NULL, 'U'},
		{"no-password", no_argument, NULL, 'w'},
		{"password", no_argument, NULL, 'W'},
		{"echo", no_argument, NULL, 'e'},
		{"quiet", no_argument, NULL, 'q'},
		{"dbname", required_argument, NULL, 'd'},
		{"analyze", no_argument, NULL, 'z'},
		{"analyze-only", no_argument, NULL, 'Z'},
		{"freeze", no_argument, NULL, 'F'},
		{"all", no_argument, NULL, 'a'},
		{"table", required_argument, NULL, 't'},
		{"full", no_argument, NULL, 'f'},
		{"verbose", no_argument, NULL, 'v'},
		{"jobs", required_argument, NULL, 'j'},
		{"maintenance-db", required_argument, NULL, 2},
		{"analyze-in-stages", no_argument, NULL, 3},
		{"disable-page-skipping", no_argument, NULL, 4},
		{"skip-locked", no_argument, NULL, 5},
		{"min-xid-age", required_argument, NULL, 6},
		{"min-mxid-age", required_argument, NULL, 7},
		{NULL, 0, NULL, 0}
	};

	const char *progname;
	int			optindex;
	int			c;
	const char *dbname = NULL;
	const char *maintenance_db = NULL;
	char	   *host = NULL;
	char	   *port = NULL;
	char	   *username = NULL;
	enum trivalue prompt_password = TRI_DEFAULT;
	bool		echo = false;
	bool		quiet = false;
	vacuumingOptions vacopts;
	bool		analyze_in_stages = false;
	bool		alldb = false;
	SimpleStringList tables = {NULL, NULL};
	int			concurrentCons = 1;
	int			tbl_count = 0;

	/* initialize options to all false */
	memset(&vacopts, 0, sizeof(vacopts));

	pg_logging_init(argv[0]);
	progname = get_progname(argv[0]);
	set_pglocale_pgservice(argv[0], PG_TEXTDOMAIN("pgscripts"));

	handle_help_version_opts(argc, argv, "vacuumdb", help);

	while ((c = getopt_long(argc, argv, "h:p:U:wWeqd:zZFat:fvj:", long_options, &optindex)) != -1)
	{
		switch (c)
		{
			case 'h':
				host = pg_strdup(optarg);
				break;
			case 'p':
				port = pg_strdup(optarg);
				break;
			case 'U':
				username = pg_strdup(optarg);
				break;
			case 'w':
				prompt_password = TRI_NO;
				break;
			case 'W':
				prompt_password = TRI_YES;
				break;
			case 'e':
				echo = true;
				break;
			case 'q':
				quiet = true;
				break;
			case 'd':
				dbname = pg_strdup(optarg);
				break;
			case 'z':
				vacopts.and_analyze = true;
				break;
			case 'Z':
				vacopts.analyze_only = true;
				break;
			case 'F':
				vacopts.freeze = true;
				break;
			case 'a':
				alldb = true;
				break;
			case 't':
				{
					simple_string_list_append(&tables, optarg);
					tbl_count++;
					break;
				}
			case 'f':
				vacopts.full = true;
				break;
			case 'v':
				vacopts.verbose = true;
				break;
			case 'j':
				concurrentCons = atoi(optarg);
				if (concurrentCons <= 0)
				{
					pg_log_error("number of parallel jobs must be at least 1");
					exit(1);
				}
				break;
			case 2:
				maintenance_db = pg_strdup(optarg);
				break;
			case 3:
				analyze_in_stages = vacopts.analyze_only = true;
				break;
			case 4:
				vacopts.disable_page_skipping = true;
				break;
			case 5:
				vacopts.skip_locked = true;
				break;
			case 6:
				vacopts.min_xid_age = atoi(optarg);
				if (vacopts.min_xid_age <= 0)
				{
					pg_log_error("minimum transaction ID age must be at least 1");
					exit(1);
				}
				break;
			case 7:
				vacopts.min_mxid_age = atoi(optarg);
				if (vacopts.min_mxid_age <= 0)
				{
					pg_log_error("minimum multixact ID age must be at least 1");
					exit(1);
				}
				break;
			default:
				fprintf(stderr, _("Try \"%s --help\" for more information.\n"), progname);
				exit(1);
		}
	}

	/*
	 * Non-option argument specifies database name as long as it wasn't
	 * already specified with -d / --dbname
	 */
	if (optind < argc && dbname == NULL)
	{
		dbname = argv[optind];
		optind++;
	}

	if (optind < argc)
	{
		pg_log_error("too many command-line arguments (first is \"%s\")",
					 argv[optind]);
		fprintf(stderr, _("Try \"%s --help\" for more information.\n"), progname);
		exit(1);
	}

	if (vacopts.analyze_only)
	{
		if (vacopts.full)
		{
			pg_log_error("cannot use the \"%s\" option when performing only analyze",
						 "full");
			exit(1);
		}
		if (vacopts.freeze)
		{
			pg_log_error("cannot use the \"%s\" option when performing only analyze",
						 "freeze");
			exit(1);
		}
		if (vacopts.disable_page_skipping)
		{
			pg_log_error("cannot use the \"%s\" option when performing only analyze",
						 "disable-page-skipping");
			exit(1);
		}
		/* allow 'and_analyze' with 'analyze_only' */
	}

	setup_cancel_handler();

	/* Avoid opening extra connections. */
	if (tbl_count && (concurrentCons > tbl_count))
		concurrentCons = tbl_count;

	if (alldb)
	{
		if (dbname)
		{
			pg_log_error("cannot vacuum all databases and a specific one at the same time");
			exit(1);
		}
		if (tables.head != NULL)
		{
			pg_log_error("cannot vacuum specific table(s) in all databases");
			exit(1);
		}

		vacuum_all_databases(&vacopts,
							 analyze_in_stages,
							 maintenance_db,
							 host, port, username, prompt_password,
							 concurrentCons,
							 progname, echo, quiet);
	}
	else
	{
		if (dbname == NULL)
		{
			if (getenv("PGDATABASE"))
				dbname = getenv("PGDATABASE");
			else if (getenv("PGUSER"))
				dbname = getenv("PGUSER");
			else
				dbname = get_user_name_or_exit(progname);
		}

		if (analyze_in_stages)
		{
			int			stage;

			for (stage = 0; stage < ANALYZE_NUM_STAGES; stage++)
			{
				vacuum_one_database(dbname, &vacopts,
									stage,
									&tables,
									host, port, username, prompt_password,
									concurrentCons,
									progname, echo, quiet);
			}
		}
		else
			vacuum_one_database(dbname, &vacopts,
								ANALYZE_NO_STAGE,
								&tables,
								host, port, username, prompt_password,
								concurrentCons,
								progname, echo, quiet);
	}

	exit(0);
}