#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int zend_long ;
typedef  int /*<<< orphan*/  sapi_module_struct ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ZEND_ATOL (int,char*) ; 
 scalar_t__* calloc (int,int) ; 
 int /*<<< orphan*/  cli_server_module_entry ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  php_cli_server_master ; 
 scalar_t__* php_cli_server_workers ; 
 int php_cli_server_workers_max ; 
 scalar_t__ php_module_startup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int sapi_cli_server_startup(sapi_module_struct *sapi_module) /* {{{ */
{
	char *workers;

	if (php_module_startup(sapi_module, &cli_server_module_entry, 1) == FAILURE) {
		return FAILURE;
	}

	if ((workers = getenv("PHP_CLI_SERVER_WORKERS"))) {
#ifndef SO_REUSEPORT
		fprintf(stderr, "platform does not support SO_REUSEPORT, cannot create workers\n");
#elif HAVE_FORK
		ZEND_ATOL(php_cli_server_workers_max, workers);

		if (php_cli_server_workers_max > 1) {
			zend_long php_cli_server_worker;
			
			php_cli_server_workers = calloc(
				php_cli_server_workers_max, sizeof(pid_t));
			if (!php_cli_server_workers) {
				php_cli_server_workers_max = 1;

				return SUCCESS;
			}

			php_cli_server_master = getpid();

			for (php_cli_server_worker = 0;
				 php_cli_server_worker < php_cli_server_workers_max;
				 php_cli_server_worker++) {
				pid_t pid = fork();

				if (pid == FAILURE) {
					/* no more forks allowed, work with what we have ... */
					php_cli_server_workers_max = 
						php_cli_server_worker + 1;
					return SUCCESS;
				} else if (pid == SUCCESS) {
					return SUCCESS;
				} else {
					php_cli_server_workers[
						php_cli_server_worker
					] = pid;
				}
			}
		} else {
			fprintf(stderr, "number of workers must be larger than 1\n");
		}
#else
		fprintf(stderr, "forking is not supported on this platform\n");
#endif
	}

	return SUCCESS;
}