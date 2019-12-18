#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ timedout; int /*<<< orphan*/  write; TYPE_3__* data; } ;
typedef  TYPE_2__ ngx_event_t ;
struct TYPE_10__ {TYPE_1__* ssl; int /*<<< orphan*/  log; } ;
typedef  TYPE_3__ ngx_connection_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* handler ) (TYPE_3__*) ;} ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_ssl_handshake (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 

__attribute__((used)) static void
ngx_ssl_handshake_handler(ngx_event_t *ev)
{
    ngx_connection_t  *c;

    c = ev->data;

    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0,
                   "SSL handshake handler: %d", ev->write);

    if (ev->timedout) {
        c->ssl->handler(c);
        return;
    }

    if (ngx_ssl_handshake(c) == NGX_AGAIN) {
        return;
    }

    c->ssl->handler(c);
}