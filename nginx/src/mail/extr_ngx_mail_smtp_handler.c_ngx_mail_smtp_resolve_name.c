#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  timeout; TYPE_3__* data; int /*<<< orphan*/  handler; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ ngx_resolver_ctx_t ;
struct TYPE_15__ {TYPE_2__* resolver_ctx; int /*<<< orphan*/  host; } ;
typedef  TYPE_3__ ngx_mail_session_t ;
struct TYPE_16__ {int /*<<< orphan*/  resolver_timeout; int /*<<< orphan*/  resolver; } ;
typedef  TYPE_4__ ngx_mail_core_srv_conf_t ;
struct TYPE_17__ {TYPE_6__* data; } ;
typedef  TYPE_5__ ngx_event_t ;
struct TYPE_18__ {TYPE_1__* read; TYPE_3__* data; } ;
typedef  TYPE_6__ ngx_connection_t ;
struct TYPE_13__ {int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_mail_close_connection (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_mail_core_module ; 
 TYPE_4__* ngx_mail_get_module_srv_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_smtp_block_reading ; 
 int /*<<< orphan*/  ngx_mail_smtp_resolve_name_handler ; 
 scalar_t__ ngx_resolve_name (TYPE_2__*) ; 
 TYPE_2__* ngx_resolve_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_mail_smtp_resolve_name(ngx_event_t *rev)
{
    ngx_connection_t          *c;
    ngx_mail_session_t        *s;
    ngx_resolver_ctx_t        *ctx;
    ngx_mail_core_srv_conf_t  *cscf;

    c = rev->data;
    s = c->data;

    cscf = ngx_mail_get_module_srv_conf(s, ngx_mail_core_module);

    ctx = ngx_resolve_start(cscf->resolver, NULL);
    if (ctx == NULL) {
        ngx_mail_close_connection(c);
        return;
    }

    ctx->name = s->host;
    ctx->handler = ngx_mail_smtp_resolve_name_handler;
    ctx->data = s;
    ctx->timeout = cscf->resolver_timeout;

    s->resolver_ctx = ctx;
    c->read->handler = ngx_mail_smtp_block_reading;

    if (ngx_resolve_name(ctx) != NGX_OK) {
        ngx_mail_close_connection(c);
    }
}