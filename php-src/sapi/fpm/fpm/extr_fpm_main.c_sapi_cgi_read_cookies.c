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
 char* FCGI_GETENV (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ SG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_context ; 

__attribute__((used)) static char *sapi_cgi_read_cookies(void) /* {{{ */
{
	fcgi_request *request = (fcgi_request*) SG(server_context);

	return FCGI_GETENV(request, "HTTP_COOKIE");
}