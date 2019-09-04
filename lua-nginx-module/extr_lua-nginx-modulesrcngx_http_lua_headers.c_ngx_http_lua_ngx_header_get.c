#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_5__ {char* data; size_t len; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_6__ {scalar_t__ transform_underscores_in_resp_headers; } ;
typedef  TYPE_2__ ngx_http_lua_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  dd (char*,int,char*,int) ; 
 scalar_t__ luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * memchr (char*,char,size_t) ; 
 int /*<<< orphan*/ * ngx_http_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_http_get_module_loc_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_check_fake_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ngx_http_lua_get_output_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 

__attribute__((used)) static int
ngx_http_lua_ngx_header_get(lua_State *L)
{
    ngx_http_request_t          *r;
    u_char                      *p, c;
    ngx_str_t                    key;
    ngx_uint_t                   i;
    size_t                       len;
    ngx_http_lua_loc_conf_t     *llcf;
    ngx_http_lua_ctx_t          *ctx;

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "no request object found");
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        return luaL_error(L, "no ctx found");
    }

    ngx_http_lua_check_fake_request(L, r);

    /* we skip the first argument that is the table */
    p = (u_char *) luaL_checklstring(L, 2, &len);

    dd("key: %.*s, len %d", (int) len, p, (int) len);

    llcf = ngx_http_get_module_loc_conf(r, ngx_http_lua_module);
    if (llcf->transform_underscores_in_resp_headers
        && memchr(p, '_', len) != NULL)
    {
        key.data = (u_char *) lua_newuserdata(L, len);
        if (key.data == NULL) {
            return luaL_error(L, "no memory");
        }

        /* replace "_" with "-" */
        for (i = 0; i < len; i++) {
            c = p[i];
            if (c == '_') {
                c = '-';
            }
            key.data[i] = c;
        }

    } else {
        key.data = p;
    }

    key.len = len;

    return ngx_http_lua_get_output_header(L, r, ctx, &key);
}