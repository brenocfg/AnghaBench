#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
struct TYPE_10__ {scalar_t__ (* handle ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*) ;TYPE_5__* in; int /*<<< orphan*/  arg; struct TYPE_10__* next; int /*<<< orphan*/ * session; int /*<<< orphan*/  (* sink ) (int /*<<< orphan*/ *,TYPE_5__*) ;int /*<<< orphan*/  detached; } ;
typedef  TYPE_1__ ngx_rtmp_netcall_session_t ;
struct TYPE_11__ {TYPE_1__* cs; } ;
typedef  TYPE_2__ ngx_rtmp_netcall_ctx_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_12__ {int destroyed; int /*<<< orphan*/ * pool; TYPE_1__* data; } ;
typedef  TYPE_3__ ngx_connection_t ;
struct TYPE_13__ {int /*<<< orphan*/  start; int /*<<< orphan*/  last; int /*<<< orphan*/  pos; } ;
typedef  TYPE_4__ ngx_buf_t ;
struct TYPE_14__ {TYPE_4__* buf; } ;

/* Variables and functions */
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_close_connection (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_finalize_session (int /*<<< orphan*/ *) ; 
 TYPE_2__* ngx_rtmp_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_netcall_module ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static void
ngx_rtmp_netcall_close(ngx_connection_t *cc)
{
    ngx_rtmp_netcall_session_t         *cs, **css;
    ngx_pool_t                         *pool;
    ngx_rtmp_session_t                 *s;
    ngx_rtmp_netcall_ctx_t             *ctx;
    ngx_buf_t                          *b;

    cs = cc->data;

    if (cc->destroyed) {
        return;
    }

    cc->destroyed = 1;

    if (!cs->detached) {
        s = cs->session;
        ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_netcall_module);

        if (cs->in && cs->sink) {
            cs->sink(cs->session, cs->in);

            b = cs->in->buf;
            b->pos = b->last = b->start;

        }

        for(css = &ctx->cs; *css; css = &((*css)->next)) {
            if (*css == cs) {
                *css = cs->next;
                break;
            }
        }

        if (cs->handle && cs->handle(s, cs->arg, cs->in) != NGX_OK) {
            ngx_rtmp_finalize_session(s);
        }
    }

    pool = cc->pool;
    ngx_close_connection(cc);
    ngx_destroy_pool(pool);
}