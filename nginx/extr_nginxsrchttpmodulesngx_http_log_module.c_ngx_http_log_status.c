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
typedef  int /*<<< orphan*/  u_char ;
typedef  int ngx_uint_t ;
struct TYPE_4__ {int status; } ;
struct TYPE_5__ {int err_status; scalar_t__ http_version; TYPE_1__ headers_out; } ;
typedef  TYPE_2__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_http_log_op_t ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_VERSION_9 ; 
 int /*<<< orphan*/ * ngx_sprintf (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static u_char *
ngx_http_log_status(ngx_http_request_t *r, u_char *buf, ngx_http_log_op_t *op)
{
    ngx_uint_t  status;

    if (r->err_status) {
        status = r->err_status;

    } else if (r->headers_out.status) {
        status = r->headers_out.status;

    } else if (r->http_version == NGX_HTTP_VERSION_9) {
        status = 9;

    } else {
        status = 0;
    }

    return ngx_sprintf(buf, "%03ui", status);
}