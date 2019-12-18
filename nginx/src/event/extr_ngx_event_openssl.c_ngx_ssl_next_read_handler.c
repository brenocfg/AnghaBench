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
struct TYPE_8__ {int ready; int available; int /*<<< orphan*/  (* handler ) (TYPE_2__*) ;scalar_t__ posted; TYPE_3__* data; } ;
typedef  TYPE_2__ ngx_event_t ;
struct TYPE_9__ {TYPE_1__* ssl; int /*<<< orphan*/  log; } ;
typedef  TYPE_3__ ngx_connection_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* next_read_handler ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  ngx_delete_posted_event (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void
ngx_ssl_next_read_handler(ngx_event_t *rev)
{
    ngx_connection_t  *c;

    c = rev->data;

    ngx_log_debug0(NGX_LOG_DEBUG_EVENT, c->log, 0, "SSL next read handler");

    rev->handler = c->ssl->next_read_handler;
    c->ssl->next_read_handler = NULL;

    if (!rev->ready) {
        rev->ready = 1;
        rev->available = -1;
    }

    if (rev->posted) {
        ngx_delete_posted_event(rev);
    }

    rev->handler(rev);
}