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
 scalar_t__ SG (int /*<<< orphan*/ ) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  fcgi_finish_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fcgi_is_fastcgi () ; 
 int /*<<< orphan*/  parent ; 
 int /*<<< orphan*/  php_handle_aborted_connection () ; 
 int /*<<< orphan*/  sapi_cgi_flush (scalar_t__) ; 
 int /*<<< orphan*/  sapi_started ; 
 int /*<<< orphan*/  server_context ; 

__attribute__((used)) static int sapi_cgi_deactivate(void)
{
	/* flush only when SAPI was started. The reasons are:
		1. SAPI Deactivate is called from two places: module init and request shutdown
		2. When the first call occurs and the request is not set up, flush fails on FastCGI.
	*/
	if (SG(sapi_started)) {
		if (fcgi_is_fastcgi()) {
			if (
				!parent &&
				!fcgi_finish_request((fcgi_request*)SG(server_context), 0)) {
				php_handle_aborted_connection();
			}
		} else {
			sapi_cgi_flush(SG(server_context));
		}
	}
	return SUCCESS;
}