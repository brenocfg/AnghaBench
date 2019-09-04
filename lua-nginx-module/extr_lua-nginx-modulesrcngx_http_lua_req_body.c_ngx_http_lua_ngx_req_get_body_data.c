#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_8__ {TYPE_1__* request_body; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_9__ {TYPE_6__* buf; struct TYPE_9__* next; } ;
typedef  TYPE_3__ ngx_chain_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_10__ {size_t last; size_t pos; } ;
struct TYPE_7__ {TYPE_3__* bufs; scalar_t__ temp_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  dd (char*,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_buf_size (TYPE_6__*) ; 
 int /*<<< orphan*/ * ngx_copy (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  ngx_http_lua_check_fake_request (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ngx_http_lua_ngx_req_get_body_data(lua_State *L)
{
    ngx_http_request_t          *r;
    int                          n;
    size_t                       len;
    ngx_chain_t                 *cl;
    u_char                      *p;
    u_char                      *buf;

    n = lua_gettop(L);

    if (n != 0) {
        return luaL_error(L, "expecting 0 arguments but seen %d", n);
    }

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "request object not found");
    }

    ngx_http_lua_check_fake_request(L, r);

    if (r->request_body == NULL
        || r->request_body->temp_file
        || r->request_body->bufs == NULL)
    {
        lua_pushnil(L);
        return 1;
    }

    cl = r->request_body->bufs;

    if (cl->next == NULL) {
        len = cl->buf->last - cl->buf->pos;

        if (len == 0) {
            lua_pushnil(L);
            return 1;
        }

        lua_pushlstring(L, (char *) cl->buf->pos, len);
        return 1;
    }

    /* found multi-buffer body */

    len = 0;

    for (; cl; cl = cl->next) {
        dd("body chunk len: %d", (int) ngx_buf_size(cl->buf));
        len += cl->buf->last - cl->buf->pos;
    }

    if (len == 0) {
        lua_pushnil(L);
        return 1;
    }

    buf = (u_char *) lua_newuserdata(L, len);

    p = buf;
    for (cl = r->request_body->bufs; cl; cl = cl->next) {
        p = ngx_copy(p, cl->buf->pos, cl->buf->last - cl->buf->pos);
    }

    lua_pushlstring(L, (char *) buf, len);
    return 1;
}