#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ StartServiceCtrlDispatcher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  st ; 

ngx_int_t
ngx_service(ngx_log_t *log)
{
    /* primary thread */

    /* StartServiceCtrlDispatcher() should be called within 30 seconds */

    if (StartServiceCtrlDispatcher(st) == 0) {
        ngx_log_error(NGX_LOG_EMERG, log, ngx_errno,
                      "StartServiceCtrlDispatcher() failed");
        return NGX_ERROR;
    }

    return NGX_OK;
}