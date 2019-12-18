#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_8__ {int len; int valid; int /*<<< orphan*/ * data; scalar_t__ not_found; scalar_t__ no_cacheable; } ;
typedef  TYPE_1__ ngx_stream_variable_value_t ;
struct TYPE_9__ {TYPE_6__* connection; } ;
typedef  TYPE_2__ ngx_stream_session_t ;
struct TYPE_10__ {int len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_11__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int NGX_SOCKADDR_STRLEN ; 
 scalar_t__ ngx_connection_local_sockaddr (TYPE_6__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_stream_variable_server_addr(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    ngx_str_t  str;
    u_char     addr[NGX_SOCKADDR_STRLEN];

    str.len = NGX_SOCKADDR_STRLEN;
    str.data = addr;

    if (ngx_connection_local_sockaddr(s->connection, &str, 0) != NGX_OK) {
        return NGX_ERROR;
    }

    str.data = ngx_pnalloc(s->connection->pool, str.len);
    if (str.data == NULL) {
        return NGX_ERROR;
    }

    ngx_memcpy(str.data, addr, str.len);

    v->len = str.len;
    v->valid = 1;
    v->no_cacheable = 0;
    v->not_found = 0;
    v->data = str.data;

    return NGX_OK;
}