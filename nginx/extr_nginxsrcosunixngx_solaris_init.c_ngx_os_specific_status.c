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

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_NOTICE ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ngx_solaris_release ; 
 int /*<<< orphan*/  ngx_solaris_sysname ; 
 int /*<<< orphan*/  ngx_solaris_version ; 

void
ngx_os_specific_status(ngx_log_t *log)
{

    ngx_log_error(NGX_LOG_NOTICE, log, 0, "OS: %s %s",
                  ngx_solaris_sysname, ngx_solaris_release);

    ngx_log_error(NGX_LOG_NOTICE, log, 0, "version: %s",
                  ngx_solaris_version);
}