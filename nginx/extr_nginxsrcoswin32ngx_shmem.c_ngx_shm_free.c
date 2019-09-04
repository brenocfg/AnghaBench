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
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  log; int /*<<< orphan*/  handle; int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ ngx_shm_t ;

/* Variables and functions */
 scalar_t__ CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 scalar_t__ UnmapViewOfFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,...) ; 

void
ngx_shm_free(ngx_shm_t *shm)
{
    if (UnmapViewOfFile(shm->addr) == 0) {
        ngx_log_error(NGX_LOG_ALERT, shm->log, ngx_errno,
                      "UnmapViewOfFile(%p) of file mapping \"%V\" failed",
                      shm->addr, &shm->name);
    }

    if (CloseHandle(shm->handle) == 0) {
        ngx_log_error(NGX_LOG_ALERT, shm->log, ngx_errno,
                      "CloseHandle() of file mapping \"%V\" failed",
                      &shm->name);
    }
}