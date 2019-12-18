#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  socklen; TYPE_2__* sockaddr; } ;
struct TYPE_22__ {int /*<<< orphan*/  timeout; TYPE_6__* data; int /*<<< orphan*/  handler; TYPE_3__ addr; } ;
typedef  TYPE_5__ ngx_resolver_ctx_t ;
struct TYPE_23__ {TYPE_5__* resolver_ctx; int /*<<< orphan*/  host; } ;
typedef  TYPE_6__ ngx_mail_session_t ;
struct TYPE_24__ {int /*<<< orphan*/  resolver_timeout; int /*<<< orphan*/ * resolver; } ;
typedef  TYPE_7__ ngx_mail_core_srv_conf_t ;
struct TYPE_25__ {TYPE_4__* read; int /*<<< orphan*/  socklen; TYPE_2__* sockaddr; TYPE_1__* log; } ;
typedef  TYPE_8__ ngx_connection_t ;
struct TYPE_21__ {int /*<<< orphan*/  handler; } ;
struct TYPE_19__ {scalar_t__ sa_family; } ;
struct TYPE_18__ {char* action; } ;

/* Variables and functions */
 scalar_t__ AF_UNIX ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_mail_close_connection (TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_mail_core_module ; 
 TYPE_7__* ngx_mail_get_module_srv_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_smtp_block_reading ; 
 int /*<<< orphan*/  ngx_mail_smtp_greeting (TYPE_6__*,TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_mail_smtp_resolve_addr_handler ; 
 scalar_t__ ngx_resolve_addr (TYPE_5__*) ; 
 TYPE_5__* ngx_resolve_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smtp_tempunavail ; 
 int /*<<< orphan*/  smtp_unavailable ; 

void
ngx_mail_smtp_init_session(ngx_mail_session_t *s, ngx_connection_t *c)
{
    ngx_resolver_ctx_t        *ctx;
    ngx_mail_core_srv_conf_t  *cscf;

    cscf = ngx_mail_get_module_srv_conf(s, ngx_mail_core_module);

    if (cscf->resolver == NULL) {
        s->host = smtp_unavailable;
        ngx_mail_smtp_greeting(s, c);
        return;
    }

#if (NGX_HAVE_UNIX_DOMAIN)
    if (c->sockaddr->sa_family == AF_UNIX) {
        s->host = smtp_tempunavail;
        ngx_mail_smtp_greeting(s, c);
        return;
    }
#endif

    c->log->action = "in resolving client address";

    ctx = ngx_resolve_start(cscf->resolver, NULL);
    if (ctx == NULL) {
        ngx_mail_close_connection(c);
        return;
    }

    ctx->addr.sockaddr = c->sockaddr;
    ctx->addr.socklen = c->socklen;
    ctx->handler = ngx_mail_smtp_resolve_addr_handler;
    ctx->data = s;
    ctx->timeout = cscf->resolver_timeout;

    s->resolver_ctx = ctx;
    c->read->handler = ngx_mail_smtp_block_reading;

    if (ngx_resolve_addr(ctx) != NGX_OK) {
        ngx_mail_close_connection(c);
    }
}