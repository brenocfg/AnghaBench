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
 int /*<<< orphan*/  fcgi_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parent ; 
 int /*<<< orphan*/  php_handle_aborted_connection () ; 

__attribute__((used)) static void sapi_fcgi_flush(void *server_context)
{
	fcgi_request *request = (fcgi_request*) server_context;

	if (
		!parent &&
		request && !fcgi_flush(request, 0)) {

		php_handle_aborted_connection();
	}
}