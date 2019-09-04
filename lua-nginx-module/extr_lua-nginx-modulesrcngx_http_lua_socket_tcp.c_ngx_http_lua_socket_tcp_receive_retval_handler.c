#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_17__ {int /*<<< orphan*/  read_event_handler; TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_18__ {int ft_type; int no_close; scalar_t__ bufs_in; scalar_t__ body_downstream; scalar_t__ raw_downstream; } ;
typedef  TYPE_3__ ngx_http_lua_socket_tcp_upstream_t ;
struct TYPE_19__ {scalar_t__ check_client_abort; } ;
typedef  TYPE_4__ ngx_http_lua_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_ctx_t ;
struct TYPE_20__ {scalar_t__ active; } ;
typedef  TYPE_5__ ngx_event_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_16__ {TYPE_5__* read; int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int NGX_HTTP_LUA_SOCKET_FT_TIMEOUT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_READ_EVENT ; 
 int NGX_USE_LEVEL_EVENT ; 
 int /*<<< orphan*/  dd (char*,scalar_t__) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ngx_add_event (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ngx_event_flags ; 
 int /*<<< orphan*/  ngx_http_block_reading ; 
 int /*<<< orphan*/ * ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_http_get_module_loc_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_rd_check_broken_connection ; 
 scalar_t__ ngx_http_lua_socket_push_input_data (TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int ngx_http_lua_socket_read_error_retval_handler (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ngx_http_lua_socket_tcp_receive_retval_handler(ngx_http_request_t *r,
    ngx_http_lua_socket_tcp_upstream_t *u, lua_State *L)
{
    int                          n;
    ngx_int_t                    rc;
    ngx_http_lua_ctx_t          *ctx;
    ngx_event_t                 *ev;

    ngx_http_lua_loc_conf_t             *llcf;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua tcp socket receive return value handler");

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);

#if 1
    if (u->raw_downstream || u->body_downstream) {
        llcf = ngx_http_get_module_loc_conf(r, ngx_http_lua_module);

        if (llcf->check_client_abort) {

            r->read_event_handler = ngx_http_lua_rd_check_broken_connection;

            ev = r->connection->read;

            dd("rev active: %d", ev->active);

            if ((ngx_event_flags & NGX_USE_LEVEL_EVENT) && !ev->active) {
                if (ngx_add_event(ev, NGX_READ_EVENT, 0) != NGX_OK) {
                    lua_pushnil(L);
                    lua_pushliteral(L, "failed to add event");
                    return 2;
                }
            }

        } else {
            /* llcf->check_client_abort == 0 */
            r->read_event_handler = ngx_http_block_reading;
        }
    }
#endif

    if (u->ft_type) {

        if (u->ft_type & NGX_HTTP_LUA_SOCKET_FT_TIMEOUT) {
            u->no_close = 1;
        }

        dd("u->bufs_in: %p", u->bufs_in);

        if (u->bufs_in) {
            rc = ngx_http_lua_socket_push_input_data(r, ctx, u, L);
            if (rc == NGX_ERROR) {
                lua_pushnil(L);
                lua_pushliteral(L, "no memory");
                return 2;
            }

            (void) ngx_http_lua_socket_read_error_retval_handler(r, u, L);

            lua_pushvalue(L, -3);
            lua_remove(L, -4);
            return 3;
        }

        n = ngx_http_lua_socket_read_error_retval_handler(r, u, L);
        lua_pushliteral(L, "");
        return n + 1;
    }

    rc = ngx_http_lua_socket_push_input_data(r, ctx, u, L);
    if (rc == NGX_ERROR) {
        lua_pushnil(L);
        lua_pushliteral(L, "no memory");
        return 2;
    }

    return 1;
}