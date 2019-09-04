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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_3__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_cycle_t ;

/* Variables and functions */
 void* CreateEvent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/ * ngx_quit_event ; 
 scalar_t__ ngx_quit_event_name ; 
 int /*<<< orphan*/ * ngx_reload_event ; 
 scalar_t__ ngx_reload_event_name ; 
 int /*<<< orphan*/ * ngx_reopen_event ; 
 scalar_t__ ngx_reopen_event_name ; 
 int /*<<< orphan*/  ngx_sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_stop_event ; 
 scalar_t__ ngx_stop_event_name ; 
 int /*<<< orphan*/  ngx_unique ; 

__attribute__((used)) static ngx_int_t
ngx_create_signal_events(ngx_cycle_t *cycle)
{
    ngx_sprintf((u_char *) ngx_stop_event_name,
                "Global\\ngx_stop_%s%Z", ngx_unique);

    ngx_stop_event = CreateEvent(NULL, 1, 0, ngx_stop_event_name);
    if (ngx_stop_event == NULL) {
        ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                      "CreateEvent(\"%s\") failed", ngx_stop_event_name);
        return NGX_ERROR;
    }


    ngx_sprintf((u_char *) ngx_quit_event_name,
                "Global\\ngx_quit_%s%Z", ngx_unique);

    ngx_quit_event = CreateEvent(NULL, 1, 0, ngx_quit_event_name);
    if (ngx_quit_event == NULL) {
        ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                      "CreateEvent(\"%s\") failed", ngx_quit_event_name);
        return NGX_ERROR;
    }


    ngx_sprintf((u_char *) ngx_reopen_event_name,
                "Global\\ngx_reopen_%s%Z", ngx_unique);

    ngx_reopen_event = CreateEvent(NULL, 1, 0, ngx_reopen_event_name);
    if (ngx_reopen_event == NULL) {
        ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                      "CreateEvent(\"%s\") failed", ngx_reopen_event_name);
        return NGX_ERROR;
    }


    ngx_sprintf((u_char *) ngx_reload_event_name,
                "Global\\ngx_reload_%s%Z", ngx_unique);

    ngx_reload_event = CreateEvent(NULL, 1, 0, ngx_reload_event_name);
    if (ngx_reload_event == NULL) {
        ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                      "CreateEvent(\"%s\") failed", ngx_reload_event_name);
        return NGX_ERROR;
    }

    return NGX_OK;
}