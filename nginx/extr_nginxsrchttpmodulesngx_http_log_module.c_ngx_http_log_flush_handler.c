#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  log; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ngx_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  ngx_http_log_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ngx_http_log_flush_handler(ngx_event_t *ev)
{
    ngx_log_debug0(NGX_LOG_DEBUG_EVENT, ev->log, 0,
                   "http log buffer flush handler");

    ngx_http_log_flush(ev->data, ev->log);
}