#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct option {char* member_0; char member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  const member_1; } ;
typedef  int /*<<< orphan*/  pw2 ;
typedef  int /*<<< orphan*/  newuser_buf ;
typedef  int /*<<< orphan*/  newpassword_buf ;
typedef  enum trivalue { ____Placeholder_trivalue } trivalue ;
struct TYPE_13__ {char* data; } ;
struct TYPE_12__ {TYPE_1__* head; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_11__ {char const* val; struct TYPE_11__* next; } ;
typedef  TYPE_1__ SimpleStringListCell ;
typedef  TYPE_2__ SimpleStringList ;
typedef  TYPE_3__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PG_TEXTDOMAIN (char*) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char* PQencryptPasswordConn (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ *) ; 
 char* PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfreemem (char*) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int TRI_DEFAULT ; 
 int TRI_NO ; 
 int TRI_YES ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_3__*,char*,char*) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_3__*,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  appendStringLiteralConn (TYPE_3__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * connectDatabase (char*,char*,char*,char*,int,char const*,int,int,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 char* fmtId (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* get_progname (char*) ; 
 char* get_user_name_or_exit (char const*) ; 
 char* getenv (char*) ; 
 int getopt_long (int,char**,char*,struct option*,int*) ; 
 int /*<<< orphan*/  handle_help_version_opts (int,char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  help ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_3__*) ; 
#define  no_argument 129 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  pg_log_error (char*,char*) ; 
 int /*<<< orphan*/  pg_logging_init (char*) ; 
 char* pg_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_3__*,char*,char*) ; 
#define  required_argument 128 
 int /*<<< orphan*/  set_pglocale_pgservice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_prompt (char*,char*,int,int) ; 
 int /*<<< orphan*/  simple_string_list_append (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ yesno_prompt (char*) ; 

int
main(int argc, char *argv[])
{
	static struct option long_options[] = {
		{"host", required_argument, NULL, 'h'},
		{"port", required_argument, NULL, 'p'},
		{"username", required_argument, NULL, 'U'},
		{"role", required_argument, NULL, 'g'},
		{"no-password", no_argument, NULL, 'w'},
		{"password", no_argument, NULL, 'W'},
		{"echo", no_argument, NULL, 'e'},
		{"createdb", no_argument, NULL, 'd'},
		{"no-createdb", no_argument, NULL, 'D'},
		{"superuser", no_argument, NULL, 's'},
		{"no-superuser", no_argument, NULL, 'S'},
		{"createrole", no_argument, NULL, 'r'},
		{"no-createrole", no_argument, NULL, 'R'},
		{"inherit", no_argument, NULL, 'i'},
		{"no-inherit", no_argument, NULL, 'I'},
		{"login", no_argument, NULL, 'l'},
		{"no-login", no_argument, NULL, 'L'},
		{"replication", no_argument, NULL, 1},
		{"no-replication", no_argument, NULL, 2},
		{"interactive", no_argument, NULL, 3},
		{"connection-limit", required_argument, NULL, 'c'},
		{"pwprompt", no_argument, NULL, 'P'},
		{"encrypted", no_argument, NULL, 'E'},
		{NULL, 0, NULL, 0}
	};

	const char *progname;
	int			optindex;
	int			c;
	const char *newuser = NULL;
	char	   *host = NULL;
	char	   *port = NULL;
	char	   *username = NULL;
	SimpleStringList roles = {NULL, NULL};
	enum trivalue prompt_password = TRI_DEFAULT;
	bool		echo = false;
	bool		interactive = false;
	char	   *conn_limit = NULL;
	bool		pwprompt = false;
	char	   *newpassword = NULL;
	char		newuser_buf[128];
	char		newpassword_buf[100];

	/* Tri-valued variables.  */
	enum trivalue createdb = TRI_DEFAULT,
				superuser = TRI_DEFAULT,
				createrole = TRI_DEFAULT,
				inherit = TRI_DEFAULT,
				login = TRI_DEFAULT,
				replication = TRI_DEFAULT;

	PQExpBufferData sql;

	PGconn	   *conn;
	PGresult   *result;

	pg_logging_init(argv[0]);
	progname = get_progname(argv[0]);
	set_pglocale_pgservice(argv[0], PG_TEXTDOMAIN("pgscripts"));

	handle_help_version_opts(argc, argv, "createuser", help);

	while ((c = getopt_long(argc, argv, "h:p:U:g:wWedDsSrRiIlLc:PE",
							long_options, &optindex)) != -1)
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
			case 'g':
				simple_string_list_append(&roles, optarg);
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
			case 'd':
				createdb = TRI_YES;
				break;
			case 'D':
				createdb = TRI_NO;
				break;
			case 's':
				superuser = TRI_YES;
				break;
			case 'S':
				superuser = TRI_NO;
				break;
			case 'r':
				createrole = TRI_YES;
				break;
			case 'R':
				createrole = TRI_NO;
				break;
			case 'i':
				inherit = TRI_YES;
				break;
			case 'I':
				inherit = TRI_NO;
				break;
			case 'l':
				login = TRI_YES;
				break;
			case 'L':
				login = TRI_NO;
				break;
			case 'c':
				conn_limit = pg_strdup(optarg);
				break;
			case 'P':
				pwprompt = true;
				break;
			case 'E':
				/* no-op, accepted for backward compatibility */
				break;
			case 1:
				replication = TRI_YES;
				break;
			case 2:
				replication = TRI_NO;
				break;
			case 3:
				interactive = true;
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
			newuser = argv[optind];
			break;
		default:
			pg_log_error("too many command-line arguments (first is \"%s\")",
						 argv[optind + 1]);
			fprintf(stderr, _("Try \"%s --help\" for more information.\n"), progname);
			exit(1);
	}

	if (newuser == NULL)
	{
		if (interactive)
		{
			simple_prompt("Enter name of role to add: ",
						  newuser_buf, sizeof(newuser_buf), true);
			newuser = newuser_buf;
		}
		else
		{
			if (getenv("PGUSER"))
				newuser = getenv("PGUSER");
			else
				newuser = get_user_name_or_exit(progname);
		}
	}

	if (pwprompt)
	{
		char		pw2[100];

		simple_prompt("Enter password for new role: ",
					  newpassword_buf, sizeof(newpassword_buf), false);
		simple_prompt("Enter it again: ", pw2, sizeof(pw2), false);
		if (strcmp(newpassword_buf, pw2) != 0)
		{
			fprintf(stderr, _("Passwords didn't match.\n"));
			exit(1);
		}
		newpassword = newpassword_buf;
	}

	if (superuser == 0)
	{
		if (interactive && yesno_prompt("Shall the new role be a superuser?"))
			superuser = TRI_YES;
		else
			superuser = TRI_NO;
	}

	if (superuser == TRI_YES)
	{
		/* Not much point in trying to restrict a superuser */
		createdb = TRI_YES;
		createrole = TRI_YES;
	}

	if (createdb == 0)
	{
		if (interactive && yesno_prompt("Shall the new role be allowed to create databases?"))
			createdb = TRI_YES;
		else
			createdb = TRI_NO;
	}

	if (createrole == 0)
	{
		if (interactive && yesno_prompt("Shall the new role be allowed to create more new roles?"))
			createrole = TRI_YES;
		else
			createrole = TRI_NO;
	}

	if (inherit == 0)
		inherit = TRI_YES;

	if (login == 0)
		login = TRI_YES;

	conn = connectDatabase("postgres", host, port, username, prompt_password,
						   progname, echo, false, false);

	initPQExpBuffer(&sql);

	printfPQExpBuffer(&sql, "CREATE ROLE %s", fmtId(newuser));
	if (newpassword)
	{
		char	   *encrypted_password;

		appendPQExpBufferStr(&sql, " PASSWORD ");

		encrypted_password = PQencryptPasswordConn(conn,
												   newpassword,
												   newuser,
												   NULL);
		if (!encrypted_password)
		{
			pg_log_error("password encryption failed: %s",
						 PQerrorMessage(conn));
			exit(1);
		}
		appendStringLiteralConn(&sql, encrypted_password, conn);
		PQfreemem(encrypted_password);
	}
	if (superuser == TRI_YES)
		appendPQExpBufferStr(&sql, " SUPERUSER");
	if (superuser == TRI_NO)
		appendPQExpBufferStr(&sql, " NOSUPERUSER");
	if (createdb == TRI_YES)
		appendPQExpBufferStr(&sql, " CREATEDB");
	if (createdb == TRI_NO)
		appendPQExpBufferStr(&sql, " NOCREATEDB");
	if (createrole == TRI_YES)
		appendPQExpBufferStr(&sql, " CREATEROLE");
	if (createrole == TRI_NO)
		appendPQExpBufferStr(&sql, " NOCREATEROLE");
	if (inherit == TRI_YES)
		appendPQExpBufferStr(&sql, " INHERIT");
	if (inherit == TRI_NO)
		appendPQExpBufferStr(&sql, " NOINHERIT");
	if (login == TRI_YES)
		appendPQExpBufferStr(&sql, " LOGIN");
	if (login == TRI_NO)
		appendPQExpBufferStr(&sql, " NOLOGIN");
	if (replication == TRI_YES)
		appendPQExpBufferStr(&sql, " REPLICATION");
	if (replication == TRI_NO)
		appendPQExpBufferStr(&sql, " NOREPLICATION");
	if (conn_limit != NULL)
		appendPQExpBuffer(&sql, " CONNECTION LIMIT %s", conn_limit);
	if (roles.head != NULL)
	{
		SimpleStringListCell *cell;

		appendPQExpBufferStr(&sql, " IN ROLE ");

		for (cell = roles.head; cell; cell = cell->next)
		{
			if (cell->next)
				appendPQExpBuffer(&sql, "%s,", fmtId(cell->val));
			else
				appendPQExpBufferStr(&sql, fmtId(cell->val));
		}
	}
	appendPQExpBufferChar(&sql, ';');

	if (echo)
		printf("%s\n", sql.data);
	result = PQexec(conn, sql.data);

	if (PQresultStatus(result) != PGRES_COMMAND_OK)
	{
		pg_log_error("creation of new role failed: %s", PQerrorMessage(conn));
		PQfinish(conn);
		exit(1);
	}

	PQclear(result);
	PQfinish(conn);
	exit(0);
}