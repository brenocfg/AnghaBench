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
struct TYPE_3__ {double start_sec; double start_msec; } ;
typedef  TYPE_1__ ngx_http_request_t ;

/* Variables and functions */

double
ngx_http_lua_ffi_req_start_time(ngx_http_request_t *r)
{
    return r->start_sec + r->start_msec / 1000.0;
}