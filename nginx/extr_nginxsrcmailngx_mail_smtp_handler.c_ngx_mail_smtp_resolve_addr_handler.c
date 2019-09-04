#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  len; } ;
struct TYPE_17__ {scalar_t__ state; TYPE_7__ name; TYPE_2__* data; } ;
typedef  TYPE_1__ ngx_resolver_ctx_t ;
struct TYPE_20__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
struct TYPE_18__ {TYPE_4__ host; TYPE_3__* connection; } ;
typedef  TYPE_2__ ngx_mail_session_t ;
struct TYPE_19__ {TYPE_8__* read; TYPE_13__* log; int /*<<< orphan*/  pool; int /*<<< orphan*/  addr_text; } ;
typedef  TYPE_3__ ngx_connection_t ;
struct TYPE_22__ {int /*<<< orphan*/  handler; } ;
struct TYPE_16__ {char* action; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_MAIL ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_RESOLVE_NXDOMAIN ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,TYPE_13__*,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,TYPE_13__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_close_connection (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_mail_smtp_greeting (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_mail_smtp_resolve_name ; 
 int /*<<< orphan*/  ngx_post_event (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_posted_events ; 
 int /*<<< orphan*/ * ngx_pstrdup (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_resolve_addr_done (TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_resolver_strerror (scalar_t__) ; 
 TYPE_4__ smtp_tempunavail ; 
 TYPE_4__ smtp_unavailable ; 

__attribute__((used)) static void
ngx_mail_smtp_resolve_addr_handler(ngx_resolver_ctx_t *ctx)
{
    ngx_connection_t    *c;
    ngx_mail_session_t  *s;

    s = ctx->data;
    c = s->connection;

    if (ctx->state) {
        ngx_log_error(NGX_LOG_ERR, c->log, 0,
                      "%V could not be resolved (%i: %s)",
                      &c->addr_text, ctx->state,
                      ngx_resolver_strerror(ctx->state));

        if (ctx->state == NGX_RESOLVE_NXDOMAIN) {
            s->host = smtp_unavailable;

        } else {
            s->host = smtp_tempunavail;
        }

        ngx_resolve_addr_done(ctx);

        ngx_mail_smtp_greeting(s, s->connection);

        return;
    }

    c->log->action = "in resolving client hostname";

    s->host.data = ngx_pstrdup(c->pool, &ctx->name);
    if (s->host.data == NULL) {
        ngx_resolve_addr_done(ctx);
        ngx_mail_close_connection(c);
        return;
    }

    s->host.len = ctx->name.len;

    ngx_resolve_addr_done(ctx);

    ngx_log_debug1(NGX_LOG_DEBUG_MAIL, c->log, 0,
                   "address resolved: %V", &s->host);

    c->read->handler = ngx_mail_smtp_resolve_name;

    ngx_post_event(c->read, &ngx_posted_events);
}