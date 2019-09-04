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
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_5__ {scalar_t__ dir; int /*<<< orphan*/  pattern; int /*<<< orphan*/  log; TYPE_1__ name; } ;
typedef  TYPE_2__ ngx_glob_t ;

/* Variables and functions */
 scalar_t__ FindClose (scalar_t__) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_free (scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
ngx_close_glob(ngx_glob_t *gl)
{
    if (gl->name.data) {
        ngx_free(gl->name.data);
    }

    if (gl->dir == INVALID_HANDLE_VALUE) {
        return;
    }

    if (FindClose(gl->dir) == 0) {
        ngx_log_error(NGX_LOG_ALERT, gl->log, ngx_errno,
                      "FindClose(%s) failed", gl->pattern);
    }
}