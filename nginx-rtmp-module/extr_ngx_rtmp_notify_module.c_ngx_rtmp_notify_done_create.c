#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
struct TYPE_11__ {int /*<<< orphan*/  url_idx; int /*<<< orphan*/ * cbname; } ;
typedef  TYPE_1__ ngx_rtmp_notify_done_t ;
struct TYPE_12__ {int /*<<< orphan*/ * args; int /*<<< orphan*/ * name; } ;
typedef  TYPE_2__ ngx_rtmp_notify_ctx_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_13__ {int /*<<< orphan*/ * next; TYPE_4__* buf; } ;
typedef  TYPE_3__ ngx_chain_t ;
struct TYPE_14__ {int /*<<< orphan*/ * last; } ;
typedef  TYPE_4__ ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ESCAPE_ARGS ; 
 TYPE_3__* ngx_alloc_chain_link (int /*<<< orphan*/ *) ; 
 void* ngx_cpymem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 TYPE_4__* ngx_create_temp_buf (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ngx_escape_uri (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_rtmp_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_rtmp_notify_create_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_rtmp_notify_module ; 
 size_t ngx_strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_chain_t *
ngx_rtmp_notify_done_create(ngx_rtmp_session_t *s, void *arg,
        ngx_pool_t *pool)
{
    ngx_rtmp_notify_done_t         *ds = arg;

    ngx_chain_t                    *pl;
    ngx_buf_t                      *b;
    size_t                          cbname_len, name_len, args_len;
    ngx_rtmp_notify_ctx_t          *ctx;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_notify_module);

    pl = ngx_alloc_chain_link(pool);
    if (pl == NULL) {
        return NULL;
    }

    cbname_len = ngx_strlen(ds->cbname);
    name_len = ctx ? ngx_strlen(ctx->name) : 0;
    args_len = ctx ? ngx_strlen(ctx->args) : 0;

    b = ngx_create_temp_buf(pool,
                            sizeof("&call=") + cbname_len +
                            sizeof("&name=") + name_len * 3 +
                            1 + args_len);
    if (b == NULL) {
        return NULL;
    }

    pl->buf = b;
    pl->next = NULL;

    b->last = ngx_cpymem(b->last, (u_char*) "&call=", sizeof("&call=") - 1);
    b->last = ngx_cpymem(b->last, ds->cbname, cbname_len);

    if (name_len) {
        b->last = ngx_cpymem(b->last, (u_char*) "&name=", sizeof("&name=") - 1);
        b->last = (u_char*) ngx_escape_uri(b->last, ctx->name, name_len,
                                           NGX_ESCAPE_ARGS);
    }

    if (args_len) {
        *b->last++ = '&';
        b->last = (u_char *) ngx_cpymem(b->last, ctx->args, args_len);
    }

    return ngx_rtmp_notify_create_request(s, pool, ds->url_idx, pl);
}