#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lwan_response {int /*<<< orphan*/  mime_type; } ;
struct lwan_request {TYPE_1__* conn; } ;
struct lwan_lua_state {int /*<<< orphan*/  L; } ;
struct lwan_lua_priv {int /*<<< orphan*/  default_type; } ;
struct cache {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int lua_Integer ;
typedef  enum lwan_http_status { ____Placeholder_lwan_http_status } lwan_http_status ;
struct TYPE_2__ {int /*<<< orphan*/  coro; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_CORO_YIELD ; 
 int HTTP_INTERNAL_ERROR ; 
 int HTTP_NOT_FOUND ; 
 int HTTP_OK ; 
#define  LUA_YIELD 128 
 scalar_t__ UNLIKELY (int) ; 
 scalar_t__ cache_coro_get_and_ref_entry (struct cache*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  coro_yield (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_handler_function (int /*<<< orphan*/ *,struct lwan_request*) ; 
 struct cache* get_or_create_cache (struct lwan_lua_priv*) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int lua_resume (int /*<<< orphan*/ *,int) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lwan_lua_state_push_request (int /*<<< orphan*/ *,struct lwan_request*) ; 
 int /*<<< orphan*/  lwan_status_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * push_newthread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum lwan_http_status lua_handle_request(struct lwan_request *request,
                                                struct lwan_response *response,
                                                void *instance)
{
    struct lwan_lua_priv *priv = instance;

    struct cache *cache = get_or_create_cache(priv);
    if (UNLIKELY(!cache))
        return HTTP_INTERNAL_ERROR;

    struct lwan_lua_state *state =
        (struct lwan_lua_state *)cache_coro_get_and_ref_entry(
            cache, request->conn->coro, "");
    if (UNLIKELY(!state))
        return HTTP_NOT_FOUND;

    lua_State *L = push_newthread(state->L, request->conn->coro);
    if (UNLIKELY(!L))
        return HTTP_INTERNAL_ERROR;

    if (UNLIKELY(!get_handler_function(L, request)))
        return HTTP_NOT_FOUND;

    int n_arguments = 1;
    lwan_lua_state_push_request(L, request);
    response->mime_type = priv->default_type;
    while (true) {
        switch (lua_resume(L, n_arguments)) {
        case LUA_YIELD:
            coro_yield(request->conn->coro, CONN_CORO_YIELD);
            n_arguments = 0;
            break;
        case 0:
            if (lua_isnil(L, -1))
                return HTTP_OK;

            if (lua_isnumber(L, -1)) {
                lua_Integer code = lua_tointeger(L, -1);

                if (code >= 100 && code <= 999)
                    return (enum lwan_http_status)code;
            }

            return HTTP_INTERNAL_ERROR;
        default:
            lwan_status_error("Error from Lua script: %s", lua_tostring(L, -1));
            return HTTP_INTERNAL_ERROR;
        }
    }
}