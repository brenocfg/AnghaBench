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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  fcgi_request ;

/* Variables and functions */
 int /*<<< orphan*/  FCGI_STDOUT ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 scalar_t__ fcgi_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ fpm_is_running ; 
 size_t fwrite (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_context ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ write (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline size_t sapi_cgibin_single_write(const char *str, uint32_t str_length) /* {{{ */
{
	ssize_t ret;

	/* sapi has started which means everything must be send through fcgi */
	if (fpm_is_running) {
		fcgi_request *request = (fcgi_request*) SG(server_context);
		ret = fcgi_write(request, FCGI_STDOUT, str, str_length);
		if (ret <= 0) {
			return 0;
		}
		return (size_t)ret;
	}

	/* sapi has not started, output to stdout instead of fcgi */
#ifdef PHP_WRITE_STDOUT
	ret = write(STDOUT_FILENO, str, str_length);
	if (ret <= 0) {
		return 0;
	}
	return (size_t)ret;
#else
	return fwrite(str, 1, MIN(str_length, 16384), stdout);
#endif
}