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
 int /*<<< orphan*/  FCGI_STDOUT ; 
 size_t INT_MAX ; 
 scalar_t__ SG (int /*<<< orphan*/ ) ; 
 int fcgi_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  php_handle_aborted_connection () ; 
 int /*<<< orphan*/  server_context ; 

__attribute__((used)) static size_t sapi_fcgi_ub_write(const char *str, size_t str_length)
{
	const char *ptr = str;
	size_t remaining = str_length;
	fcgi_request *request = (fcgi_request*) SG(server_context);

	while (remaining > 0) {
		int to_write = remaining > INT_MAX ? INT_MAX : (int)remaining;
		int ret = fcgi_write(request, FCGI_STDOUT, ptr, to_write);

		if (ret <= 0) {
			php_handle_aborted_connection();
			return str_length - remaining;
		}
		ptr += ret;
		remaining -= ret;
	}

	return str_length;
}