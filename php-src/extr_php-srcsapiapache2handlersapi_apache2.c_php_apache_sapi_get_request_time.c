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
struct TYPE_5__ {TYPE_1__* r; } ;
typedef  TYPE_2__ php_struct ;
struct TYPE_4__ {int /*<<< orphan*/  request_time; } ;

/* Variables and functions */
 TYPE_2__* SG (int /*<<< orphan*/ ) ; 
 scalar_t__ apr_time_as_msec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_context ; 

__attribute__((used)) static double php_apache_sapi_get_request_time(void)
{
	php_struct *ctx = SG(server_context);
	return ((double) apr_time_as_msec(ctx->r->request_time)) / 1000.0;
}