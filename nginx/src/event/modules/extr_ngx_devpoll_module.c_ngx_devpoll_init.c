#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  ngx_msec_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_event_t ;
struct TYPE_6__ {int changes; int events; } ;
typedef  TYPE_1__ ngx_devpoll_conf_t ;
struct TYPE_7__ {int /*<<< orphan*/  log; int /*<<< orphan*/  conf_ctx; } ;
typedef  TYPE_2__ ngx_cycle_t ;
struct TYPE_8__ {int /*<<< orphan*/  actions; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_OK ; 
 int NGX_USE_FD_EVENT ; 
 int NGX_USE_LEVEL_EVENT ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/ * change_index ; 
 int /*<<< orphan*/ * change_list ; 
 int dp ; 
 int /*<<< orphan*/ * event_list ; 
 int max_changes ; 
 int nchanges ; 
 int nevents ; 
 int /*<<< orphan*/ * ngx_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_devpoll_module ; 
 TYPE_4__ ngx_devpoll_module_ctx ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_event_actions ; 
 int ngx_event_flags ; 
 TYPE_1__* ngx_event_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_io ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_os_io ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ write (int,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_devpoll_init(ngx_cycle_t *cycle, ngx_msec_t timer)
{
    size_t               n;
    ngx_devpoll_conf_t  *dpcf;

    dpcf = ngx_event_get_conf(cycle->conf_ctx, ngx_devpoll_module);

    if (dp == -1) {
        dp = open("/dev/poll", O_RDWR);

        if (dp == -1) {
            ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_errno,
                          "open(/dev/poll) failed");
            return NGX_ERROR;
        }
    }

    if (max_changes < dpcf->changes) {
        if (nchanges) {
            n = nchanges * sizeof(struct pollfd);
            if (write(dp, change_list, n) != (ssize_t) n) {
                ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                              "write(/dev/poll) failed");
                return NGX_ERROR;
            }

            nchanges = 0;
        }

        if (change_list) {
            ngx_free(change_list);
        }

        change_list = ngx_alloc(sizeof(struct pollfd) * dpcf->changes,
                                cycle->log);
        if (change_list == NULL) {
            return NGX_ERROR;
        }

        if (change_index) {
            ngx_free(change_index);
        }

        change_index = ngx_alloc(sizeof(ngx_event_t *) * dpcf->changes,
                                 cycle->log);
        if (change_index == NULL) {
            return NGX_ERROR;
        }
    }

    max_changes = dpcf->changes;

    if (nevents < dpcf->events) {
        if (event_list) {
            ngx_free(event_list);
        }

        event_list = ngx_alloc(sizeof(struct pollfd) * dpcf->events,
                               cycle->log);
        if (event_list == NULL) {
            return NGX_ERROR;
        }
    }

    nevents = dpcf->events;

    ngx_io = ngx_os_io;

    ngx_event_actions = ngx_devpoll_module_ctx.actions;

    ngx_event_flags = NGX_USE_LEVEL_EVENT|NGX_USE_FD_EVENT;

    return NGX_OK;
}