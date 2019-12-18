#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct option {char* member_0; char member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  const member_1; } ;
typedef  enum trivalue { ____Placeholder_trivalue } trivalue ;
struct TYPE_5__ {TYPE_1__* head; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/ * val; struct TYPE_4__* next; } ;
typedef  TYPE_1__ SimpleStringListCell ;
typedef  TYPE_2__ SimpleStringList ;

/* Variables and functions */
 int /*<<< orphan*/  PG_TEXTDOMAIN (char*) ; 
 int TRI_DEFAULT ; 
 int TRI_NO ; 
 int TRI_YES ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  cluster_all_databases (int,char const*,char*,char*,char*,int,char const*,int,int) ; 
 int /*<<< orphan*/  cluster_one_database (char const*,int,int /*<<< orphan*/ *,char*,char*,char*,int,char const*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 char* get_progname (char*) ; 
 char* get_user_name_or_exit (char const*) ; 
 char* getenv (char*) ; 
 int getopt_long (int,char**,char*,struct option*,int*) ; 
 int /*<<< orphan*/  handle_help_version_opts (int,char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  help ; 
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
		{"all", no_argument, NULL, 'a'},
		{"table", required_argument, NULL, 't'},
		{"verbose", no_argument, NULL, 'v'},
		{"maintenance-db", required_argument, NULL, 2},
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
	bool		alldb = false;
	bool		verbose = false;
	SimpleStringList tables = {NULL, NULL};

	pg_logging_init(argv[0]);
	progname = get_progname(argv[0]);
	set_pglocale_pgservice(argv[0], PG_TEXTDOMAIN("pgscripts"));

	handle_help_version_opts(argc, argv, "clusterdb", help);

	while ((c = getopt_long(argc, argv, "h:p:U:wWeqd:at:v", long_options, &optindex)) != -1)
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
			case 'a':
				alldb = true;
				break;
			case 't':
				simple_string_list_append(&tables, optarg);
				break;
			case 'v':
				verbose = true;
				break;
			case 2:
				maintenance_db = pg_strdup(optarg);
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

	setup_cancel_handler();

	if (alldb)
	{
		if (dbname)
		{
			pg_log_error("cannot cluster all databases and a specific one at the same time");
			exit(1);
		}

		if (tables.head != NULL)
		{
			pg_log_error("cannot cluster specific table(s) in all databases");
			exit(1);
		}

		cluster_all_databases(verbose, maintenance_db, host, port, username, prompt_password,
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

		if (tables.head != NULL)
		{
			SimpleStringListCell *cell;

			for (cell = tables.head; cell; cell = cell->next)
			{
				cluster_one_database(dbname, verbose, cell->val,
									 host, port, username, prompt_password,
									 progname, echo);
			}
		}
		else
			cluster_one_database(dbname, verbose, NULL,
								 host, port, username, prompt_password,
								 progname, echo);
	}

	exit(0);
}