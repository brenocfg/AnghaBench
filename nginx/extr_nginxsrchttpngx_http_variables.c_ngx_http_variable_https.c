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
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_variable_value_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_variable_null_value ; 

__attribute__((used)) static ngx_int_t
ngx_http_variable_https(ngx_http_request_t *r,
    ngx_http_variable_value_t *v, uintptr_t data)
{
#if (NGX_HTTP_SSL)

    if (r->connection->ssl) {
        v->len = sizeof("on") - 1;
        v->valid = 1;
        v->no_cacheable = 0;
        v->not_found = 0;
        v->data = (u_char *) "on";

        return NGX_OK;
    }

#endif

    *v = ngx_http_variable_null_value;

    return NGX_OK;
}