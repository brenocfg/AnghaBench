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
struct TYPE_4__ {int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_1__ zend_stat_t ;
typedef  int /*<<< orphan*/  opt_struct ;
struct TYPE_5__ {scalar_t__ phpinfo_as_text; } ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  PHP_CLI_SERVER_LOG_PROCESS ; 
 int /*<<< orphan*/  PHP_VERSION ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 char* VCWD_GETCWD (char*,int) ; 
 char* VCWD_GETWD (char*) ; 
 scalar_t__ VCWD_REALPATH (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 scalar_t__ php_cli_server_ctor (int /*<<< orphan*/ *,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  php_cli_server_do_event_loop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_cli_server_dtor (int /*<<< orphan*/ *) ; 
 int php_cli_server_log_level ; 
 int /*<<< orphan*/  php_cli_server_logf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  php_cli_server_sigint_handler ; 
 int php_getopt (int,char**,int /*<<< orphan*/  const*,char**,int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ php_sys_stat (char const*,TYPE_1__*) ; 
 TYPE_2__ sapi_module ; 
 int /*<<< orphan*/  server ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  zend_signal_init () ; 

int do_cli_server(int argc, char **argv) /* {{{ */
{
	char *php_optarg = NULL;
	int php_optind = 1;
	int c;
	const char *server_bind_address = NULL;
	extern const opt_struct OPTIONS[];
	const char *document_root = NULL;
#ifdef PHP_WIN32
	char document_root_tmp[MAXPATHLEN];
	size_t k;
#endif
	const char *router = NULL;
	char document_root_buf[MAXPATHLEN];

	while ((c = php_getopt(argc, argv, OPTIONS, &php_optarg, &php_optind, 0, 2))!=-1) {
		switch (c) {
			case 'S':
				server_bind_address = php_optarg;
				break;
			case 't':
#ifndef PHP_WIN32
				document_root = php_optarg;
#else
				k = strlen(php_optarg);
				if (k + 1 > MAXPATHLEN) {
					fprintf(stderr, "Document root path is too long.\n");
					return 1;
				}
				memmove(document_root_tmp, php_optarg, k + 1);
				/* Clean out any trailing garbage that might have been passed
					from a batch script. */
				do {
					document_root_tmp[k] = '\0';
					k--;
				} while ('"' == document_root_tmp[k] || ' ' == document_root_tmp[k]);
				document_root = document_root_tmp;
#endif
				break;
			case 'q':
				if (php_cli_server_log_level > 1) {
					php_cli_server_log_level--;
				}
				break;
		}
	}

	if (document_root) {
		zend_stat_t sb;

		if (php_sys_stat(document_root, &sb)) {
			fprintf(stderr, "Directory %s does not exist.\n", document_root);
			return 1;
		}
		if (!S_ISDIR(sb.st_mode)) {
			fprintf(stderr, "%s is not a directory.\n", document_root);
			return 1;
		}
		if (VCWD_REALPATH(document_root, document_root_buf)) {
			document_root = document_root_buf;
		}
	} else {
		char *ret = NULL;

#if HAVE_GETCWD
		ret = VCWD_GETCWD(document_root_buf, MAXPATHLEN);
#elif HAVE_GETWD
		ret = VCWD_GETWD(document_root_buf);
#endif
		document_root = ret ? document_root_buf: ".";
	}

	if (argc > php_optind) {
		router = argv[php_optind];
	}

	if (FAILURE == php_cli_server_ctor(&server, server_bind_address, document_root, router)) {
		return 1;
	}
	sapi_module.phpinfo_as_text = 0;

	{
		php_cli_server_logf(
			PHP_CLI_SERVER_LOG_PROCESS,
			"PHP %s Development Server (http://%s) started",
			PHP_VERSION, server_bind_address);
	}

#if defined(SIGINT)
	signal(SIGINT, php_cli_server_sigint_handler);
#endif

#if defined(SIGPIPE)
	signal(SIGPIPE, SIG_IGN);
#endif

	zend_signal_init();

	php_cli_server_do_event_loop(&server);
	php_cli_server_dtor(&server);
	return 0;
}