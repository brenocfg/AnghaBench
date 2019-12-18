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
typedef  int /*<<< orphan*/  request_rec ;
struct TYPE_3__ {int /*<<< orphan*/ * r; } ;
typedef  TYPE_1__ php_struct ;

/* Variables and functions */
 TYPE_1__* SG (int /*<<< orphan*/ ) ; 
 scalar_t__ ap_rwrite (char const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_handle_aborted_connection () ; 
 int /*<<< orphan*/  server_context ; 

__attribute__((used)) static size_t
php_apache_sapi_ub_write(const char *str, size_t str_length)
{
	request_rec *r;
	php_struct *ctx;

	ctx = SG(server_context);
	r = ctx->r;

	if (ap_rwrite(str, str_length, r) < 0) {
		php_handle_aborted_connection();
	}

	return str_length; /* we always consume all the data passed to us. */
}