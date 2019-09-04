#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  log; scalar_t__ timedout; TYPE_3__* data; } ;
typedef  TYPE_2__ ngx_event_t ;
struct TYPE_9__ {int timedout; TYPE_1__* ssl; } ;
typedef  TYPE_3__ ngx_connection_t ;
typedef  int /*<<< orphan*/  (* ngx_connection_handler_pt ) (TYPE_3__*) ;
struct TYPE_7__ {int /*<<< orphan*/  (* handler ) (TYPE_3__*) ;} ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ngx_ssl_shutdown (TYPE_3__*) ; 

__attribute__((used)) static void
ngx_ssl_shutdown_handler(ngx_event_t *ev)
{
    ngx_connection_t           *c;
    ngx_connection_handler_pt   handler;

    c = ev->data;
    handler = c->ssl->handler;

    if (ev->timedout) {
        c->timedout = 1;
    }

    ngx_log_debug0(NGX_LOG_DEBUG_EVENT, ev->log, 0, "SSL shutdown handler");

    if (ngx_ssl_shutdown(c) == NGX_AGAIN) {
        return;
    }

    handler(c);
}