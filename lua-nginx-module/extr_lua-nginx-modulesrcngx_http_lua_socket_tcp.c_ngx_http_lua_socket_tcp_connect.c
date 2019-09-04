#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_26__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_27__ {int /*<<< orphan*/  log; int /*<<< orphan*/  log_error; scalar_t__ connection; } ;
typedef  TYPE_3__ ngx_peer_connection_t ;
typedef  void* ngx_msec_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_28__ {TYPE_1__* connection; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_29__ {int /*<<< orphan*/ * socket_pool; TYPE_6__* conf; void* read_timeout; void* send_timeout; void* connect_timeout; TYPE_3__ peer; TYPE_4__* request; scalar_t__ raw_downstream; scalar_t__ body_downstream; } ;
typedef  TYPE_5__ ngx_http_lua_socket_tcp_upstream_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_socket_pool_t ;
struct TYPE_30__ {scalar_t__ pool_size; void* read_timeout; void* send_timeout; void* connect_timeout; } ;
typedef  TYPE_6__ ngx_http_lua_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_25__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int LUA_REGISTRYINDEX ; 
#define  LUA_TNIL 130 
#define  LUA_TNUMBER 129 
#define  LUA_TSTRING 128 
 scalar_t__ LUA_TTABLE ; 
 int /*<<< orphan*/  NGX_ERROR_ERR ; 
 int NGX_HTTP_LUA_CONTEXT_ACCESS ; 
 int NGX_HTTP_LUA_CONTEXT_CONTENT ; 
 int NGX_HTTP_LUA_CONTEXT_REWRITE ; 
 int NGX_HTTP_LUA_CONTEXT_SSL_CERT ; 
 int NGX_HTTP_LUA_CONTEXT_SSL_SESS_FETCH ; 
 int NGX_HTTP_LUA_CONTEXT_TIMER ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  SOCKET_CONNECT_TIMEOUT_INDEX ; 
 int /*<<< orphan*/  SOCKET_CTX_INDEX ; 
 int /*<<< orphan*/  SOCKET_KEY_INDEX ; 
 int /*<<< orphan*/  SOCKET_READ_TIMEOUT_INDEX ; 
 int /*<<< orphan*/  SOCKET_SEND_TIMEOUT_INDEX ; 
 int /*<<< orphan*/  dd (char*,int /*<<< orphan*/ ) ; 
 int luaL_argerror (int /*<<< orphan*/ *,int,char const*) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int luaL_typename (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_concat (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 TYPE_5__* lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 char* lua_pushfstring (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_tolstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 void* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int lua_typename (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * ngx_http_get_module_ctx (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* ngx_http_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_check_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_4__* ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_lightudata_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_socket_check_busy_connecting (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_check_busy_reading (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_check_busy_writing (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int ngx_http_lua_socket_tcp_connect_helper (int /*<<< orphan*/ *,TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_create_socket_pool (int /*<<< orphan*/ *,TYPE_4__*,TYPE_2__,scalar_t__,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_finalize (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 
 int /*<<< orphan*/  socket_pool_key ; 
 int /*<<< orphan*/  upstream_udata_metatable_key ; 

__attribute__((used)) static int
ngx_http_lua_socket_tcp_connect(lua_State *L)
{
    ngx_http_request_t          *r;
    ngx_http_lua_ctx_t          *ctx;
    int                          port;
    int                          n;
    u_char                      *p;
    size_t                       len;
    ngx_http_lua_loc_conf_t     *llcf;
    ngx_peer_connection_t       *pc;
    int                          connect_timeout, send_timeout, read_timeout;
    unsigned                     custom_pool;
    int                          key_index;
    ngx_int_t                    backlog;
    ngx_int_t                    pool_size;
    ngx_str_t                    key;
    const char                  *msg;

    ngx_http_lua_socket_tcp_upstream_t      *u;

    ngx_http_lua_socket_pool_t              *spool;

    n = lua_gettop(L);
    if (n != 2 && n != 3 && n != 4) {
        return luaL_error(L, "ngx.socket connect: expecting 2, 3, or 4 "
                          "arguments (including the object), but seen %d", n);
    }

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "no request found");
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        return luaL_error(L, "no ctx found");
    }

    ngx_http_lua_check_context(L, ctx, NGX_HTTP_LUA_CONTEXT_REWRITE
                               | NGX_HTTP_LUA_CONTEXT_ACCESS
                               | NGX_HTTP_LUA_CONTEXT_CONTENT
                               | NGX_HTTP_LUA_CONTEXT_TIMER
                               | NGX_HTTP_LUA_CONTEXT_SSL_CERT
                               | NGX_HTTP_LUA_CONTEXT_SSL_SESS_FETCH);

    luaL_checktype(L, 1, LUA_TTABLE);

    p = (u_char *) luaL_checklstring(L, 2, &len);

    backlog = -1;
    key_index = 2;
    pool_size = 0;
    custom_pool = 0;
    llcf = ngx_http_get_module_loc_conf(r, ngx_http_lua_module);

    if (lua_type(L, n) == LUA_TTABLE) {

        /* found the last optional option table */

        lua_getfield(L, n, "pool_size");

        if (lua_isnumber(L, -1)) {
            pool_size = (ngx_int_t) lua_tointeger(L, -1);

            if (pool_size <= 0) {
                msg = lua_pushfstring(L, "bad \"pool_size\" option value: %i",
                                      pool_size);
                return luaL_argerror(L, n, msg);
            }

        } else if (!lua_isnil(L, -1)) {
            msg = lua_pushfstring(L, "bad \"pool_size\" option type: %s",
                                  lua_typename(L, lua_type(L, -1)));
            return luaL_argerror(L, n, msg);
        }

        lua_pop(L, 1);

        lua_getfield(L, n, "backlog");

        if (lua_isnumber(L, -1)) {
            backlog = (ngx_int_t) lua_tointeger(L, -1);

            if (backlog < 0) {
                msg = lua_pushfstring(L, "bad \"backlog\" option value: %i",
                                      backlog);
                return luaL_argerror(L, n, msg);
            }

            /* use default value for pool size if only backlog specified */
            if (pool_size == 0) {
                pool_size = llcf->pool_size;
            }
        }

        lua_pop(L, 1);

        lua_getfield(L, n, "pool");

        switch (lua_type(L, -1)) {
        case LUA_TNUMBER:
            lua_tostring(L, -1);
            /* FALLTHROUGH */

        case LUA_TSTRING:
            custom_pool = 1;

            lua_pushvalue(L, -1);
            lua_rawseti(L, 1, SOCKET_KEY_INDEX);

            key_index = n + 1;

            break;

        case LUA_TNIL:
            lua_pop(L, 2);
            break;

        default:
            msg = lua_pushfstring(L, "bad \"pool\" option type: %s",
                                  luaL_typename(L, -1));
            luaL_argerror(L, n, msg);
            break;
        }

        n--;
    }

    /* the fourth argument is not a table */
    if (n == 4) {
        lua_pop(L, 1);
        n--;
    }

    if (n == 3) {
        port = luaL_checkinteger(L, 3);

        if (port < 0 || port > 65535) {
            lua_pushnil(L);
            lua_pushfstring(L, "bad port number: %d", port);
            return 2;
        }

        if (!custom_pool) {
            lua_pushliteral(L, ":");
            lua_insert(L, 3);
            lua_concat(L, 3);
        }

        dd("socket key: %s", lua_tostring(L, -1));

    } else { /* n == 2 */
        port = 0;
    }

    if (!custom_pool) {
        /* the key's index is 2 */

        lua_pushvalue(L, 2);
        lua_rawseti(L, 1, SOCKET_KEY_INDEX);
    }

    lua_rawgeti(L, 1, SOCKET_CTX_INDEX);
    u = lua_touserdata(L, -1);
    lua_pop(L, 1);

    if (u) {
        if (u->request && u->request != r) {
            return luaL_error(L, "bad request");
        }

        ngx_http_lua_socket_check_busy_connecting(r, u, L);
        ngx_http_lua_socket_check_busy_reading(r, u, L);
        ngx_http_lua_socket_check_busy_writing(r, u, L);

        if (u->body_downstream || u->raw_downstream) {
            return luaL_error(L, "attempt to re-connect a request socket");
        }

        if (u->peer.connection) {
            ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "lua tcp socket reconnect without shutting down");

            ngx_http_lua_socket_tcp_finalize(r, u);
        }

        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "lua reuse socket upstream ctx");

    } else {
        u = lua_newuserdata(L, sizeof(ngx_http_lua_socket_tcp_upstream_t));
        if (u == NULL) {
            return luaL_error(L, "no memory");
        }

#if 1
        lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                              upstream_udata_metatable_key));
        lua_rawget(L, LUA_REGISTRYINDEX);
        lua_setmetatable(L, -2);
#endif

        lua_rawseti(L, 1, SOCKET_CTX_INDEX);
    }

    ngx_memzero(u, sizeof(ngx_http_lua_socket_tcp_upstream_t));

    u->request = r; /* set the controlling request */

    u->conf = llcf;

    pc = &u->peer;

    pc->log = r->connection->log;
    pc->log_error = NGX_ERROR_ERR;

    dd("lua peer connection log: %p", pc->log);

    lua_rawgeti(L, 1, SOCKET_CONNECT_TIMEOUT_INDEX);
    lua_rawgeti(L, 1, SOCKET_SEND_TIMEOUT_INDEX);
    lua_rawgeti(L, 1, SOCKET_READ_TIMEOUT_INDEX);

    read_timeout = (ngx_int_t) lua_tointeger(L, -1);
    send_timeout = (ngx_int_t) lua_tointeger(L, -2);
    connect_timeout = (ngx_int_t) lua_tointeger(L, -3);

    lua_pop(L, 3);

    if (connect_timeout > 0) {
        u->connect_timeout = (ngx_msec_t) connect_timeout;

    } else {
        u->connect_timeout = u->conf->connect_timeout;
    }

    if (send_timeout > 0) {
        u->send_timeout = (ngx_msec_t) send_timeout;

    } else {
        u->send_timeout = u->conf->send_timeout;
    }

    if (read_timeout > 0) {
        u->read_timeout = (ngx_msec_t) read_timeout;

    } else {
        u->read_timeout = u->conf->read_timeout;
    }

    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(socket_pool_key));
    lua_rawget(L, LUA_REGISTRYINDEX); /* table */
    lua_pushvalue(L, key_index); /* key */

    lua_rawget(L, -2);
    spool = lua_touserdata(L, -1);
    lua_pop(L, 1);

    if (spool != NULL) {
        u->socket_pool = spool;

    } else if (pool_size > 0) {
        lua_pushvalue(L, key_index);
        key.data = (u_char *) lua_tolstring(L, -1, &key.len);

        ngx_http_lua_socket_tcp_create_socket_pool(L, r, key, pool_size,
                                                   backlog, &spool);
        u->socket_pool = spool;
    }

    return ngx_http_lua_socket_tcp_connect_helper(L, u, r, ctx, p,
                                                  len, port, 0);
}