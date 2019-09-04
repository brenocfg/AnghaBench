#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__* data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  (* ngx_ssl_variable_handler_pt ) (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {size_t len; int valid; int not_found; scalar_t__ no_cacheable; scalar_t__* data; } ;
typedef  TYPE_4__ ngx_http_variable_value_t ;
struct TYPE_11__ {TYPE_2__* connection; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_9__ {scalar_t__ ssl; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 

__attribute__((used)) static ngx_int_t
ngx_http_ssl_static_variable(ngx_http_request_t *r,
    ngx_http_variable_value_t *v, uintptr_t data)
{
    ngx_ssl_variable_handler_pt  handler = (ngx_ssl_variable_handler_pt) data;

    size_t     len;
    ngx_str_t  s;

    if (r->connection->ssl) {

        (void) handler(r->connection, NULL, &s);

        v->data = s.data;

        for (len = 0; v->data[len]; len++) { /* void */ }

        v->len = len;
        v->valid = 1;
        v->no_cacheable = 0;
        v->not_found = 0;

        return NGX_OK;
    }

    v->not_found = 1;

    return NGX_OK;
}