#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {int valid; int /*<<< orphan*/ * data; scalar_t__ not_found; scalar_t__ no_cacheable; int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ ngx_http_variable_value_t ;
struct TYPE_6__ {scalar_t__ status; } ;
struct TYPE_8__ {scalar_t__ keepalive; TYPE_1__ headers_out; } ;
typedef  TYPE_3__ ngx_http_request_t ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_SWITCHING_PROTOCOLS ; 
 int /*<<< orphan*/  NGX_OK ; 

__attribute__((used)) static ngx_int_t
ngx_http_variable_sent_connection(ngx_http_request_t *r,
    ngx_http_variable_value_t *v, uintptr_t data)
{
    size_t   len;
    char    *p;

    if (r->headers_out.status == NGX_HTTP_SWITCHING_PROTOCOLS) {
        len = sizeof("upgrade") - 1;
        p = "upgrade";

    } else if (r->keepalive) {
        len = sizeof("keep-alive") - 1;
        p = "keep-alive";

    } else {
        len = sizeof("close") - 1;
        p = "close";
    }

    v->len = len;
    v->valid = 1;
    v->no_cacheable = 0;
    v->not_found = 0;
    v->data = (u_char *) p;

    return NGX_OK;
}