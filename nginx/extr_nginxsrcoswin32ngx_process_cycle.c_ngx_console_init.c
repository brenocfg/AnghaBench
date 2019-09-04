#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  log; int /*<<< orphan*/  conf_ctx; } ;
typedef  TYPE_1__ ngx_cycle_t ;
struct TYPE_5__ {scalar_t__ daemon; } ;
typedef  TYPE_2__ ngx_core_conf_t ;

/* Variables and functions */
 scalar_t__ FreeConsole () ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 scalar_t__ SetConsoleCtrlHandler (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_console_handler ; 
 int /*<<< orphan*/  ngx_core_module ; 
 int /*<<< orphan*/  ngx_errno ; 
 scalar_t__ ngx_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ngx_console_init(ngx_cycle_t *cycle)
{
    ngx_core_conf_t  *ccf;

    ccf = (ngx_core_conf_t *) ngx_get_conf(cycle->conf_ctx, ngx_core_module);

    if (ccf->daemon) {
        if (FreeConsole() == 0) {
            ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                          "FreeConsole() failed");
        }

        return;
    }

    if (SetConsoleCtrlHandler(ngx_console_handler, 1) == 0) {
        ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                      "SetConsoleCtrlHandler() failed");
    }
}