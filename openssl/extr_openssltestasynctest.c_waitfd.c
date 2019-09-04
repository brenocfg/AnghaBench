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
typedef  int /*<<< orphan*/  ASYNC_WAIT_CTX ;
typedef  int /*<<< orphan*/  ASYNC_JOB ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_WAIT_CTX_clear_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASYNC_WAIT_CTX_set_wait_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASYNC_get_current_job () ; 
 int /*<<< orphan*/ * ASYNC_get_wait_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASYNC_pause_job () ; 
 int /*<<< orphan*/  MAGIC_WAIT_FD ; 

__attribute__((used)) static int waitfd(void *args)
{
    ASYNC_JOB *job;
    ASYNC_WAIT_CTX *waitctx;
    job = ASYNC_get_current_job();
    if (job == NULL)
        return 0;
    waitctx = ASYNC_get_wait_ctx(job);
    if (waitctx == NULL)
        return 0;

    /* First case: no fd added or removed */
    ASYNC_pause_job();

    /* Second case: one fd added */
    if (!ASYNC_WAIT_CTX_set_wait_fd(waitctx, waitctx, MAGIC_WAIT_FD, NULL, NULL))
        return 0;
    ASYNC_pause_job();

    /* Third case: all fd removed */
    if (!ASYNC_WAIT_CTX_clear_fd(waitctx, waitctx))
        return 0;
    ASYNC_pause_job();

    /* Last case: fd added and immediately removed */
    if (!ASYNC_WAIT_CTX_set_wait_fd(waitctx, waitctx, MAGIC_WAIT_FD, NULL, NULL))
        return 0;
    if (!ASYNC_WAIT_CTX_clear_fd(waitctx, waitctx))
        return 0;

    return 1;
}