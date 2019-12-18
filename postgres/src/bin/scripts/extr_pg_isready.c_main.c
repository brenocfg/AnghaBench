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
struct TYPE_4__ {char* val; scalar_t__ keyword; } ;
typedef  TYPE_1__ PQconninfoOption ;
typedef  int PGPing ;

/* Variables and functions */
 char* DEFAULT_CONNECT_TIMEOUT ; 
 char* DEFAULT_PGSOCKET_DIR ; 
 int PARAMS_ARRAY_SIZE ; 
 int /*<<< orphan*/  PG_TEXTDOMAIN (char*) ; 
#define  PQPING_NO_ATTEMPT 133 
#define  PQPING_NO_RESPONSE 132 
#define  PQPING_OK 131 
#define  PQPING_REJECT 130 
 TYPE_1__* PQconndefaults () ; 
 TYPE_1__* PQconninfoParse (char const*,char**) ; 
 int PQpingParams (char const**,char const**,int) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 char* get_progname (char*) ; 
 int getopt_long (int,char**,char*,struct option*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_help_version_opts (int,char**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  help ; 
#define  no_argument 129 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int /*<<< orphan*/  pg_logging_init (char*) ; 
 char* pg_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
#define  required_argument 128 
 int /*<<< orphan*/  set_pglocale_pgservice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

int
main(int argc, char **argv)
{
	int			c;

	const char *progname;

	const char *pghost = NULL;
	const char *pgport = NULL;
	const char *pguser = NULL;
	const char *pgdbname = NULL;
	const char *connect_timeout = DEFAULT_CONNECT_TIMEOUT;

	const char *pghost_str = NULL;
	const char *pghostaddr_str = NULL;
	const char *pgport_str = NULL;

#define PARAMS_ARRAY_SIZE	7

	const char *keywords[PARAMS_ARRAY_SIZE];
	const char *values[PARAMS_ARRAY_SIZE];

	bool		quiet = false;

	PGPing		rv;
	PQconninfoOption *opts = NULL;
	PQconninfoOption *defs = NULL;
	PQconninfoOption *opt;
	PQconninfoOption *def;
	char	   *errmsg = NULL;

	/*
	 * We accept user and database as options to avoid useless errors from
	 * connecting with invalid params
	 */

	static struct option long_options[] = {
		{"dbname", required_argument, NULL, 'd'},
		{"host", required_argument, NULL, 'h'},
		{"port", required_argument, NULL, 'p'},
		{"quiet", no_argument, NULL, 'q'},
		{"timeout", required_argument, NULL, 't'},
		{"username", required_argument, NULL, 'U'},
		{NULL, 0, NULL, 0}
	};

	pg_logging_init(argv[0]);
	progname = get_progname(argv[0]);
	set_pglocale_pgservice(argv[0], PG_TEXTDOMAIN("pgscripts"));
	handle_help_version_opts(argc, argv, progname, help);

	while ((c = getopt_long(argc, argv, "d:h:p:qt:U:", long_options, NULL)) != -1)
	{
		switch (c)
		{
			case 'd':
				pgdbname = pg_strdup(optarg);
				break;
			case 'h':
				pghost = pg_strdup(optarg);
				break;
			case 'p':
				pgport = pg_strdup(optarg);
				break;
			case 'q':
				quiet = true;
				break;
			case 't':
				connect_timeout = pg_strdup(optarg);
				break;
			case 'U':
				pguser = pg_strdup(optarg);
				break;
			default:
				fprintf(stderr, _("Try \"%s --help\" for more information.\n"), progname);

				/*
				 * We need to make sure we don't return 1 here because someone
				 * checking the return code might infer unintended meaning
				 */
				exit(PQPING_NO_ATTEMPT);
		}
	}

	if (optind < argc)
	{
		pg_log_error("too many command-line arguments (first is \"%s\")",
					 argv[optind]);
		fprintf(stderr, _("Try \"%s --help\" for more information.\n"), progname);

		/*
		 * We need to make sure we don't return 1 here because someone
		 * checking the return code might infer unintended meaning
		 */
		exit(PQPING_NO_ATTEMPT);
	}

	keywords[0] = "host";
	values[0] = pghost;
	keywords[1] = "port";
	values[1] = pgport;
	keywords[2] = "user";
	values[2] = pguser;
	keywords[3] = "dbname";
	values[3] = pgdbname;
	keywords[4] = "connect_timeout";
	values[4] = connect_timeout;
	keywords[5] = "fallback_application_name";
	values[5] = progname;
	keywords[6] = NULL;
	values[6] = NULL;

	/*
	 * Get the host and port so we can display them in our output
	 */
	if (pgdbname &&
		(strncmp(pgdbname, "postgresql://", 13) == 0 ||
		 strncmp(pgdbname, "postgres://", 11) == 0 ||
		 strchr(pgdbname, '=') != NULL))
	{
		opts = PQconninfoParse(pgdbname, &errmsg);
		if (opts == NULL)
		{
			pg_log_error("%s", errmsg);
			exit(PQPING_NO_ATTEMPT);
		}
	}

	defs = PQconndefaults();
	if (defs == NULL)
	{
		pg_log_error("could not fetch default options");
		exit(PQPING_NO_ATTEMPT);
	}

	for (opt = opts, def = defs; def->keyword; def++)
	{
		if (strcmp(def->keyword, "host") == 0)
		{
			if (opt && opt->val)
				pghost_str = opt->val;
			else if (pghost)
				pghost_str = pghost;
			else if (def->val)
				pghost_str = def->val;
			else
				pghost_str = DEFAULT_PGSOCKET_DIR;
		}
		else if (strcmp(def->keyword, "hostaddr") == 0)
		{
			if (opt && opt->val)
				pghostaddr_str = opt->val;
			else if (def->val)
				pghostaddr_str = def->val;
		}
		else if (strcmp(def->keyword, "port") == 0)
		{
			if (opt && opt->val)
				pgport_str = opt->val;
			else if (pgport)
				pgport_str = pgport;
			else if (def->val)
				pgport_str = def->val;
		}

		if (opt)
			opt++;
	}

	rv = PQpingParams(keywords, values, 1);

	if (!quiet)
	{
		printf("%s:%s - ",
			   pghostaddr_str != NULL ? pghostaddr_str : pghost_str,
			   pgport_str);

		switch (rv)
		{
			case PQPING_OK:
				printf(_("accepting connections\n"));
				break;
			case PQPING_REJECT:
				printf(_("rejecting connections\n"));
				break;
			case PQPING_NO_RESPONSE:
				printf(_("no response\n"));
				break;
			case PQPING_NO_ATTEMPT:
				printf(_("no attempt\n"));
				break;
			default:
				printf(_("unknown\n"));
		}
	}

	exit(rv);
}