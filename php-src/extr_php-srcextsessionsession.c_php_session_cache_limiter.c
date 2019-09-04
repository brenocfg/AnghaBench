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
struct TYPE_3__ {int /*<<< orphan*/  (* func ) () ;scalar_t__ name; } ;
typedef  TYPE_1__ php_session_cache_limiter_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 char* PS (int /*<<< orphan*/ ) ; 
 scalar_t__ SG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_limiter ; 
 int /*<<< orphan*/  headers_sent ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 char* php_output_get_start_filename () ; 
 int php_output_get_start_lineno () ; 
 int /*<<< orphan*/  php_session_abort () ; 
 char* php_session_active ; 
 TYPE_1__* php_session_cache_limiters ; 
 int /*<<< orphan*/  session_status ; 
 int /*<<< orphan*/  strcasecmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int php_session_cache_limiter(void) /* {{{ */
{
	const php_session_cache_limiter_t *lim;

	if (PS(cache_limiter)[0] == '\0') return 0;
	if (PS(session_status) != php_session_active) return -1;

	if (SG(headers_sent)) {
		const char *output_start_filename = php_output_get_start_filename();
		int output_start_lineno = php_output_get_start_lineno();

		php_session_abort();
		if (output_start_filename) {
			php_error_docref(NULL, E_WARNING, "Cannot send session cache limiter - headers already sent (output started at %s:%d)", output_start_filename, output_start_lineno);
		} else {
			php_error_docref(NULL, E_WARNING, "Cannot send session cache limiter - headers already sent");
		}
		return -2;
	}

	for (lim = php_session_cache_limiters; lim->name; lim++) {
		if (!strcasecmp(lim->name, PS(cache_limiter))) {
			lim->func();
			return 0;
		}
	}

	return -1;
}