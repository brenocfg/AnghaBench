#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/ * ngx_tid_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  scalar_t__ ngx_err_t ;
struct TYPE_4__ {int /*<<< orphan*/ * log; } ;
typedef  TYPE_1__ ngx_cycle_t ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateEvent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  EVENT_MODIFY_STATE ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_CORE ; 
 int /*<<< orphan*/  NGX_LOG_NOTICE ; 
 int NGX_PROCESS_SYNC_NAME ; 
 int /*<<< orphan*/ * OpenEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * OpenMutex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ResetEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYNCHRONIZE ; 
 scalar_t__ SetEvent (int /*<<< orphan*/ *) ; 
 scalar_t__ WAIT_FAILED ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForMultipleObjects (scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  ngx_cache_loader_thread ; 
 int /*<<< orphan*/ * ngx_cache_manager_event ; 
 int /*<<< orphan*/ * ngx_cache_manager_mutex ; 
 scalar_t__ ngx_cache_manager_mutex_name ; 
 int /*<<< orphan*/  ngx_cache_manager_thread ; 
 int /*<<< orphan*/  ngx_close_handle (int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_create_thread (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_errno ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  ngx_pid ; 
 int ngx_quit ; 
 int ngx_reopen ; 
 int /*<<< orphan*/  ngx_sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int ngx_terminate ; 
 int /*<<< orphan*/  ngx_time_update () ; 
 int /*<<< orphan*/  ngx_unique ; 
 int /*<<< orphan*/  ngx_worker_process_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_worker_thread ; 

__attribute__((used)) static void
ngx_worker_process_cycle(ngx_cycle_t *cycle, char *mevn)
{
    char        wtevn[NGX_PROCESS_SYNC_NAME];
    char        wqevn[NGX_PROCESS_SYNC_NAME];
    char        wroevn[NGX_PROCESS_SYNC_NAME];
    HANDLE      mev, events[3];
    u_long      nev, ev;
    ngx_err_t   err;
    ngx_tid_t   wtid, cmtid, cltid;
    ngx_log_t  *log;

    log = cycle->log;

    ngx_log_debug0(NGX_LOG_DEBUG_CORE, log, 0, "worker started");

    ngx_sprintf((u_char *) wtevn, "ngx_worker_term_%P%Z", ngx_pid);
    events[0] = CreateEvent(NULL, 1, 0, wtevn);
    if (events[0] == NULL) {
        ngx_log_error(NGX_LOG_ALERT, log, ngx_errno,
                      "CreateEvent(\"%s\") failed", wtevn);
        goto failed;
    }

    ngx_sprintf((u_char *) wqevn, "ngx_worker_quit_%P%Z", ngx_pid);
    events[1] = CreateEvent(NULL, 1, 0, wqevn);
    if (events[1] == NULL) {
        ngx_log_error(NGX_LOG_ALERT, log, ngx_errno,
                      "CreateEvent(\"%s\") failed", wqevn);
        goto failed;
    }

    ngx_sprintf((u_char *) wroevn, "ngx_worker_reopen_%P%Z", ngx_pid);
    events[2] = CreateEvent(NULL, 1, 0, wroevn);
    if (events[2] == NULL) {
        ngx_log_error(NGX_LOG_ALERT, log, ngx_errno,
                      "CreateEvent(\"%s\") failed", wroevn);
        goto failed;
    }

    mev = OpenEvent(EVENT_MODIFY_STATE, 0, mevn);
    if (mev == NULL) {
        ngx_log_error(NGX_LOG_ALERT, log, ngx_errno,
                      "OpenEvent(\"%s\") failed", mevn);
        goto failed;
    }

    if (SetEvent(mev) == 0) {
        ngx_log_error(NGX_LOG_ALERT, log, ngx_errno,
                      "SetEvent(\"%s\") failed", mevn);
        goto failed;
    }


    ngx_sprintf((u_char *) ngx_cache_manager_mutex_name,
                "ngx_cache_manager_mutex_%s%Z", ngx_unique);

    ngx_cache_manager_mutex = OpenMutex(SYNCHRONIZE, 0,
                                        ngx_cache_manager_mutex_name);
    if (ngx_cache_manager_mutex == NULL) {
        ngx_log_error(NGX_LOG_ALERT, log, ngx_errno,
                      "OpenMutex(\"%s\") failed", ngx_cache_manager_mutex_name);
        goto failed;
    }

    ngx_cache_manager_event = CreateEvent(NULL, 1, 0, NULL);
    if (ngx_cache_manager_event == NULL) {
        ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                      "CreateEvent(\"ngx_cache_manager_event\") failed");
        goto failed;
    }


    if (ngx_create_thread(&wtid, ngx_worker_thread, NULL, log) != 0) {
        goto failed;
    }

    if (ngx_create_thread(&cmtid, ngx_cache_manager_thread, NULL, log) != 0) {
        goto failed;
    }

    if (ngx_create_thread(&cltid, ngx_cache_loader_thread, NULL, log) != 0) {
        goto failed;
    }

    for ( ;; ) {
        ev = WaitForMultipleObjects(3, events, 0, INFINITE);

        err = ngx_errno;
        ngx_time_update();

        ngx_log_debug1(NGX_LOG_DEBUG_CORE, log, 0,
                       "worker WaitForMultipleObjects: %ul", ev);

        if (ev == WAIT_OBJECT_0) {
            ngx_terminate = 1;
            ngx_log_error(NGX_LOG_NOTICE, log, 0, "exiting");

            if (ResetEvent(events[0]) == 0) {
                ngx_log_error(NGX_LOG_ALERT, log, 0,
                              "ResetEvent(\"%s\") failed", wtevn);
            }

            break;
        }

        if (ev == WAIT_OBJECT_0 + 1) {
            ngx_quit = 1;
            ngx_log_error(NGX_LOG_NOTICE, log, 0, "gracefully shutting down");
            break;
        }

        if (ev == WAIT_OBJECT_0 + 2) {
            ngx_reopen = 1;
            ngx_log_error(NGX_LOG_NOTICE, log, 0, "reopening logs");

            if (ResetEvent(events[2]) == 0) {
                ngx_log_error(NGX_LOG_ALERT, log, 0,
                              "ResetEvent(\"%s\") failed", wroevn);
            }

            continue;
        }

        if (ev == WAIT_FAILED) {
            ngx_log_error(NGX_LOG_ALERT, log, err,
                          "WaitForMultipleObjects() failed");

            goto failed;
        }
    }

    /* wait threads */

    if (SetEvent(ngx_cache_manager_event) == 0) {
        ngx_log_error(NGX_LOG_ALERT, log, ngx_errno,
                      "SetEvent(\"ngx_cache_manager_event\") failed");
    }

    events[1] = wtid;
    events[2] = cmtid;

    nev = 3;

    for ( ;; ) {
        ev = WaitForMultipleObjects(nev, events, 0, INFINITE);

        err = ngx_errno;
        ngx_time_update();

        ngx_log_debug1(NGX_LOG_DEBUG_CORE, log, 0,
                       "worker exit WaitForMultipleObjects: %ul", ev);

        if (ev == WAIT_OBJECT_0) {
            break;
        }

        if (ev == WAIT_OBJECT_0 + 1) {
            if (nev == 2) {
                break;
            }

            events[1] = events[2];
            nev = 2;
            continue;
        }

        if (ev == WAIT_OBJECT_0 + 2) {
            nev = 2;
            continue;
        }

        if (ev == WAIT_FAILED) {
            ngx_log_error(NGX_LOG_ALERT, log, err,
                          "WaitForMultipleObjects() failed");
            break;
        }
    }

    ngx_close_handle(ngx_cache_manager_event);
    ngx_close_handle(events[0]);
    ngx_close_handle(events[1]);
    ngx_close_handle(events[2]);
    ngx_close_handle(mev);

    ngx_worker_process_exit(cycle);

failed:

    exit(2);
}