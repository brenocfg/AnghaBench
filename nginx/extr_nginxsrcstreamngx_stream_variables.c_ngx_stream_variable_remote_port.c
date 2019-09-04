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
typedef  int ngx_uint_t ;
struct TYPE_7__ {int valid; int /*<<< orphan*/ * data; int /*<<< orphan*/ * len; scalar_t__ not_found; scalar_t__ no_cacheable; } ;
typedef  TYPE_2__ ngx_stream_variable_value_t ;
struct TYPE_8__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_stream_session_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_6__ {int /*<<< orphan*/  sockaddr; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int ngx_inet_get_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ngx_sprintf (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_stream_variable_remote_port(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    ngx_uint_t  port;

    v->len = 0;
    v->valid = 1;
    v->no_cacheable = 0;
    v->not_found = 0;

    v->data = ngx_pnalloc(s->connection->pool, sizeof("65535") - 1);
    if (v->data == NULL) {
        return NGX_ERROR;
    }

    port = ngx_inet_get_port(s->connection->sockaddr);

    if (port > 0 && port < 65536) {
        v->len = ngx_sprintf(v->data, "%ui", port) - v->data;
    }

    return NGX_OK;
}