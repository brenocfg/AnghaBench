#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_resolver_t ;
struct TYPE_9__ {scalar_t__ timeout; int ident; TYPE_5__* event; int /*<<< orphan*/  cancelable; } ;
typedef  TYPE_2__ ngx_resolver_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_event_t ;
struct TYPE_10__ {int /*<<< orphan*/  cancelable; int /*<<< orphan*/  log; TYPE_2__* data; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_5__*,scalar_t__) ; 
 TYPE_5__* ngx_resolver_calloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ngx_resolver_timeout_handler ; 

__attribute__((used)) static ngx_int_t
ngx_resolver_set_timeout(ngx_resolver_t *r, ngx_resolver_ctx_t *ctx)
{
    if (ctx->event || ctx->timeout == 0) {
        return NGX_OK;
    }

    ctx->event = ngx_resolver_calloc(r, sizeof(ngx_event_t));
    if (ctx->event == NULL) {
        return NGX_ERROR;
    }

    ctx->event->handler = ngx_resolver_timeout_handler;
    ctx->event->data = ctx;
    ctx->event->log = r->log;
    ctx->event->cancelable = ctx->cancelable;
    ctx->ident = -1;

    ngx_add_timer(ctx->event, ctx->timeout);

    return NGX_OK;
}