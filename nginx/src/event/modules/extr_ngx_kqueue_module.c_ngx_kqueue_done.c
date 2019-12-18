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
struct TYPE_3__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_cycle_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/ * change_list ; 
 int close (int) ; 
 int /*<<< orphan*/ * event_list ; 
 scalar_t__ max_changes ; 
 scalar_t__ nchanges ; 
 scalar_t__ nevents ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_free (int /*<<< orphan*/ *) ; 
 int ngx_kqueue ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ngx_kqueue_done(ngx_cycle_t *cycle)
{
    if (close(ngx_kqueue) == -1) {
        ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                      "kqueue close() failed");
    }

    ngx_kqueue = -1;

    ngx_free(change_list);
    ngx_free(event_list);

    change_list = NULL;
    event_list = NULL;
    max_changes = 0;
    nchanges = 0;
    nevents = 0;
}