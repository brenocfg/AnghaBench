#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_12__ {TYPE_4__* connection; } ;
typedef  TYPE_2__ ngx_stream_session_t ;
struct TYPE_11__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {TYPE_1__ addr_text; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
typedef  TYPE_3__ ngx_stream_realip_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_14__ {TYPE_1__ addr_text; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_15__ {int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
typedef  TYPE_5__ ngx_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int NGX_SOCKADDR_STRLEN ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 TYPE_3__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 
 size_t ngx_sock_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_realip_module ; 
 int /*<<< orphan*/  ngx_stream_set_ctx (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_stream_realip_set_addr(ngx_stream_session_t *s, ngx_addr_t *addr)
{
    size_t                    len;
    u_char                   *p;
    u_char                    text[NGX_SOCKADDR_STRLEN];
    ngx_connection_t         *c;
    ngx_stream_realip_ctx_t  *ctx;

    c = s->connection;

    ctx = ngx_palloc(c->pool, sizeof(ngx_stream_realip_ctx_t));
    if (ctx == NULL) {
        return NGX_ERROR;
    }

    len = ngx_sock_ntop(addr->sockaddr, addr->socklen, text,
                        NGX_SOCKADDR_STRLEN, 0);
    if (len == 0) {
        return NGX_ERROR;
    }

    p = ngx_pnalloc(c->pool, len);
    if (p == NULL) {
        return NGX_ERROR;
    }

    ngx_memcpy(p, text, len);

    ngx_stream_set_ctx(s, ctx, ngx_stream_realip_module);

    ctx->sockaddr = c->sockaddr;
    ctx->socklen = c->socklen;
    ctx->addr_text = c->addr_text;

    c->sockaddr = addr->sockaddr;
    c->socklen = addr->socklen;
    c->addr_text.len = len;
    c->addr_text.data = p;

    return NGX_DECLINED;
}