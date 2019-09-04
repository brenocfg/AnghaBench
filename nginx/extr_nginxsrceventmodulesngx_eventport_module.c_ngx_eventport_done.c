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
typedef  scalar_t__ timer_t ;
struct TYPE_3__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_cycle_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int close (int) ; 
 int ep ; 
 int /*<<< orphan*/ * event_list ; 
 scalar_t__ event_timer ; 
 scalar_t__ nevents ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int timer_delete (scalar_t__) ; 

__attribute__((used)) static void
ngx_eventport_done(ngx_cycle_t *cycle)
{
    if (event_timer != (timer_t) -1) {
        if (timer_delete(event_timer) == -1) {
            ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                          "timer_delete() failed");
        }

        event_timer = (timer_t) -1;
    }

    if (close(ep) == -1) {
        ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                      "close() event port failed");
    }

    ep = -1;

    ngx_free(event_list);

    event_list = NULL;
    nevents = 0;
}