#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct option {char* member_0; char member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  const member_1; } ;
typedef  enum trivalue { ____Placeholder_trivalue } trivalue ;
struct TYPE_4__ {int /*<<< orphan*/ * head; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ SimpleStringList ;

/* Variables and functions */
 int /*<<< orphan*/  PG_TEXTDOMAIN (char*) ; 
 int /*<<< orphan*/  REINDEX_DATABASE ; 
 int /*<<< orphan*/  REINDEX_INDEX ; 
 int /*<<< orphan*/  REINDEX_SCHEMA ; 
 int /*<<< orphan*/  REINDEX_SYSTEM ; 
 int /*<<< orphan*/  REINDEX_TABLE ; 
 int TRI_DEFAULT ; 
 int TRI_NO ; 
 int TRI_YES ; 
 char* _ (char*) ; 
 int atoi (int /*<<< orphan*/ ) ; 
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
 char* pg_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reindex_all_databases (char const*,char const*,char const*,char const*,int,char const*,int,int,int,int,int) ; 
 int /*<<< orphan*/  reindex_one_database (char const*,int /*<<< orphan*/ ,TYPE_1__*,char const*,char const*,char const*,int,char const*,int,int,int,int) ; 
#define  required_argument 128 
 int /*<<< orphan*/  set_pglocale_pgservice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_cancel_handler () ; 
 int /*<<< orphan*/  simple_string_list_append (TYPE_1__*,int /*<<< orphan*/ ) ; 
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
		{"schema", required_argument, NULL, 'S'},
		{"dbname", required_argument, NULL, 'd'},
		{"all", no_argument, NULL, 'a'},
		{"system", no_argument, NULL, 's'},
		{"table", required_argument, NULL, 't'},
		{"index", required_argument, NULL, 'i'},
		{"jobs", required_argument, NULL, 'j'},
		{"verbose", no_argument, NULL, 'v'},
		{"concurrently", no_argument, NULL, 1},
		{"maintenance-db", required_argument, NULL, 2},
		{NULL, 0, NULL, 0}
	};

	const char *progname;
	int			optindex;
	int			c;

	const char *dbname = NULL;
	const char *maintenance_db = NULL;
	const char *host = NULL;
	const char *port = NULL;
	const char *username = NULL;
	enum trivalue prompt_password = TRI_DEFAULT;
	bool		syscatalog = false;
	bool		alldb = false;
	bool		echo = false;
	bool		quiet = false;
	bool		verbose = false;
	bool		concurrently = false;
	SimpleStringList indexes = {NULL, NULL};
	SimpleStringList tables = {NULL, NULL};
	SimpleStringList schemas = {NULL, NULL};
	int			concurrentCons = 1;

	pg_logging_init(argv[0]);
	progname = get_progname(argv[0]);
	set_pglocale_pgservice(argv[0], PG_TEXTDOMAIN("pgscripts"));

	handle_help_version_opts(argc, argv, "reindexdb", help);

	/* process command-line options */
	while ((c = getopt_long(argc, argv, "h:p:U:wWeqS:d:ast:i:j:v", long_options, &optindex)) != -1)
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
			case 'S':
				simple_string_list_append(&schemas, optarg);
				break;
			case 'd':
				dbname = pg_strdup(optarg);
				break;
			case 'a':
				alldb = true;
				break;
			case 's':
				syscatalog = true;
				break;
			case 't':
				simple_string_list_append(&tables, optarg);
				break;
			case 'i':
				simple_string_list_append(&indexes, optarg);
				break;
			case 'j':
				concurrentCons = atoi(optarg);
				if (concurrentCons <= 0)
				{
					pg_log_error("number of parallel jobs must be at least 1");
					exit(1);
				}
				break;
			case 'v':
				verbose = true;
				break;
			case 1:
				concurrently = true;
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
			pg_log_error("cannot reindex all databases and a specific one at the same time");
			exit(1);
		}
		if (syscatalog)
		{
			pg_log_error("cannot reindex all databases and system catalogs at the same time");
			exit(1);
		}
		if (schemas.head != NULL)
		{
			pg_log_error("cannot reindex specific schema(s) in all databases");
			exit(1);
		}
		if (tables.head != NULL)
		{
			pg_log_error("cannot reindex specific table(s) in all databases");
			exit(1);
		}
		if (indexes.head != NULL)
		{
			pg_log_error("cannot reindex specific index(es) in all databases");
			exit(1);
		}

		reindex_all_databases(maintenance_db, host, port, username,
							  prompt_password, progname, echo, quiet, verbose,
							  concurrently, concurrentCons);
	}
	else if (syscatalog)
	{
		if (schemas.head != NULL)
		{
			pg_log_error("cannot reindex specific schema(s) and system catalogs at the same time");
			exit(1);
		}
		if (tables.head != NULL)
		{
			pg_log_error("cannot reindex specific table(s) and system catalogs at the same time");
			exit(1);
		}
		if (indexes.head != NULL)
		{
			pg_log_error("cannot reindex specific index(es) and system catalogs at the same time");
			exit(1);
		}

		if (concurrentCons > 1)
		{
			pg_log_error("cannot use multiple jobs to reindex system catalogs");
			exit(1);
		}

		if (dbname == NULL)
		{
			if (getenv("PGDATABASE"))
				dbname = getenv("PGDATABASE");
			else if (getenv("PGUSER"))
				dbname = getenv("PGUSER");
			else
				dbname = get_user_name_or_exit(progname);
		}

		reindex_one_database(dbname, REINDEX_SYSTEM, NULL, host,
							 port, username, prompt_password, progname,
							 echo, verbose, concurrently, 1);
	}
	else
	{
		/*
		 * Index-level REINDEX is not supported with multiple jobs as we
		 * cannot control the concurrent processing of multiple indexes
		 * depending on the same relation.
		 */
		if (concurrentCons > 1 && indexes.head != NULL)
		{
			pg_log_error("cannot use multiple jobs to reindex indexes");
			exit(1);
		}

		if (dbname == NULL)
		{
			if (getenv("PGDATABASE"))
				dbname = getenv("PGDATABASE");
			else if (getenv("PGUSER"))
				dbname = getenv("PGUSER");
			else
				dbname = get_user_name_or_exit(progname);
		}

		if (schemas.head != NULL)
			reindex_one_database(dbname, REINDEX_SCHEMA, &schemas, host,
								 port, username, prompt_password, progname,
								 echo, verbose, concurrently, concurrentCons);

		if (indexes.head != NULL)
			reindex_one_database(dbname, REINDEX_INDEX, &indexes, host,
								 port, username, prompt_password, progname,
								 echo, verbose, concurrently, 1);

		if (tables.head != NULL)
			reindex_one_database(dbname, REINDEX_TABLE, &tables, host,
								 port, username, prompt_password, progname,
								 echo, verbose, concurrently,
								 concurrentCons);

		/*
		 * reindex database only if neither index nor table nor schema is
		 * specified
		 */
		if (indexes.head == NULL && tables.head == NULL && schemas.head == NULL)
			reindex_one_database(dbname, REINDEX_DATABASE, NULL, host,
								 port, username, prompt_password, progname,
								 echo, verbose, concurrently, concurrentCons);
	}

	exit(0);
}