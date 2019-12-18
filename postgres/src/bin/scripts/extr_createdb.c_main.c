#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct option {char* member_0; char member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  const member_1; } ;
typedef  enum trivalue { ____Placeholder_trivalue } trivalue ;
struct TYPE_7__ {char* data; } ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PG_TEXTDOMAIN (char*) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char* PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int TRI_DEFAULT ; 
 int TRI_NO ; 
 int TRI_YES ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendStringLiteralConn (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * connectMaintenanceDatabase (char const*,char*,char*,char*,int,char const*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 char* fmtId (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 char* get_progname (char*) ; 
 char* get_user_name_or_exit (char const*) ; 
 char* getenv (char*) ; 
 int getopt_long (int,char**,char*,struct option*,int*) ; 
 int /*<<< orphan*/  handle_help_version_opts (int,char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  help ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
#define  no_argument 129 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 scalar_t__ pg_char_to_encoding (char*) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int /*<<< orphan*/  pg_logging_init (char*) ; 
 void* pg_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_1__*,char*,char*) ; 
#define  required_argument 128 
 int /*<<< orphan*/  set_pglocale_pgservice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 

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
		{"owner", required_argument, NULL, 'O'},
		{"tablespace", required_argument, NULL, 'D'},
		{"template", required_argument, NULL, 'T'},
		{"encoding", required_argument, NULL, 'E'},
		{"lc-collate", required_argument, NULL, 1},
		{"lc-ctype", required_argument, NULL, 2},
		{"locale", required_argument, NULL, 'l'},
		{"maintenance-db", required_argument, NULL, 3},
		{NULL, 0, NULL, 0}
	};

	const char *progname;
	int			optindex;
	int			c;

	const char *dbname = NULL;
	const char *maintenance_db = NULL;
	char	   *comment = NULL;
	char	   *host = NULL;
	char	   *port = NULL;
	char	   *username = NULL;
	enum trivalue prompt_password = TRI_DEFAULT;
	bool		echo = false;
	char	   *owner = NULL;
	char	   *tablespace = NULL;
	char	   *template = NULL;
	char	   *encoding = NULL;
	char	   *lc_collate = NULL;
	char	   *lc_ctype = NULL;
	char	   *locale = NULL;

	PQExpBufferData sql;

	PGconn	   *conn;
	PGresult   *result;

	pg_logging_init(argv[0]);
	progname = get_progname(argv[0]);
	set_pglocale_pgservice(argv[0], PG_TEXTDOMAIN("pgscripts"));

	handle_help_version_opts(argc, argv, "createdb", help);

	while ((c = getopt_long(argc, argv, "h:p:U:wWeO:D:T:E:l:", long_options, &optindex)) != -1)
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
			case 'O':
				owner = pg_strdup(optarg);
				break;
			case 'D':
				tablespace = pg_strdup(optarg);
				break;
			case 'T':
				template = pg_strdup(optarg);
				break;
			case 'E':
				encoding = pg_strdup(optarg);
				break;
			case 1:
				lc_collate = pg_strdup(optarg);
				break;
			case 2:
				lc_ctype = pg_strdup(optarg);
				break;
			case 'l':
				locale = pg_strdup(optarg);
				break;
			case 3:
				maintenance_db = pg_strdup(optarg);
				break;
			default:
				fprintf(stderr, _("Try \"%s --help\" for more information.\n"), progname);
				exit(1);
		}
	}

	switch (argc - optind)
	{
		case 0:
			break;
		case 1:
			dbname = argv[optind];
			break;
		case 2:
			dbname = argv[optind];
			comment = argv[optind + 1];
			break;
		default:
			pg_log_error("too many command-line arguments (first is \"%s\")",
						 argv[optind + 2]);
			fprintf(stderr, _("Try \"%s --help\" for more information.\n"), progname);
			exit(1);
	}

	if (locale)
	{
		if (lc_ctype)
		{
			pg_log_error("only one of --locale and --lc-ctype can be specified");
			exit(1);
		}
		if (lc_collate)
		{
			pg_log_error("only one of --locale and --lc-collate can be specified");
			exit(1);
		}
		lc_ctype = locale;
		lc_collate = locale;
	}

	if (encoding)
	{
		if (pg_char_to_encoding(encoding) < 0)
		{
			pg_log_error("\"%s\" is not a valid encoding name", encoding);
			exit(1);
		}
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

	initPQExpBuffer(&sql);

	appendPQExpBuffer(&sql, "CREATE DATABASE %s",
					  fmtId(dbname));

	if (owner)
		appendPQExpBuffer(&sql, " OWNER %s", fmtId(owner));
	if (tablespace)
		appendPQExpBuffer(&sql, " TABLESPACE %s", fmtId(tablespace));
	if (encoding)
		appendPQExpBuffer(&sql, " ENCODING '%s'", encoding);
	if (template)
		appendPQExpBuffer(&sql, " TEMPLATE %s", fmtId(template));
	if (lc_collate)
		appendPQExpBuffer(&sql, " LC_COLLATE '%s'", lc_collate);
	if (lc_ctype)
		appendPQExpBuffer(&sql, " LC_CTYPE '%s'", lc_ctype);

	appendPQExpBufferChar(&sql, ';');

	/* No point in trying to use postgres db when creating postgres db. */
	if (maintenance_db == NULL && strcmp(dbname, "postgres") == 0)
		maintenance_db = "template1";

	conn = connectMaintenanceDatabase(maintenance_db, host, port, username,
									  prompt_password, progname, echo);

	if (echo)
		printf("%s\n", sql.data);
	result = PQexec(conn, sql.data);

	if (PQresultStatus(result) != PGRES_COMMAND_OK)
	{
		pg_log_error("database creation failed: %s", PQerrorMessage(conn));
		PQfinish(conn);
		exit(1);
	}

	PQclear(result);

	if (comment)
	{
		printfPQExpBuffer(&sql, "COMMENT ON DATABASE %s IS ", fmtId(dbname));
		appendStringLiteralConn(&sql, comment, conn);
		appendPQExpBufferChar(&sql, ';');

		if (echo)
			printf("%s\n", sql.data);
		result = PQexec(conn, sql.data);

		if (PQresultStatus(result) != PGRES_COMMAND_OK)
		{
			pg_log_error("comment creation failed (database was created): %s",
						 PQerrorMessage(conn));
			PQfinish(conn);
			exit(1);
		}

		PQclear(result);
	}

	PQfinish(conn);

	exit(0);
}