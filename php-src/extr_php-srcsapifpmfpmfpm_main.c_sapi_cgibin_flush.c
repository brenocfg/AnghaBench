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
typedef  int /*<<< orphan*/  fcgi_request ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  fcgi_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fpm_is_running ; 
 int /*<<< orphan*/  parent ; 
 int /*<<< orphan*/  php_handle_aborted_connection () ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void sapi_cgibin_flush(void *server_context) /* {{{ */
{
	/* fpm has started, let use fcgi instead of stdout */
	if (fpm_is_running) {
		fcgi_request *request = (fcgi_request*) server_context;
		if (!parent && request && !fcgi_flush(request, 0)) {
			php_handle_aborted_connection();
		}
		return;
	}

	/* fpm has not started yet, let use stdout instead of fcgi */
	if (fflush(stdout) == EOF) {
		php_handle_aborted_connection();
	}
}