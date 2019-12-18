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
 scalar_t__ ASYNC_FINISH ; 
 scalar_t__ ASYNC_PAUSE ; 
 int /*<<< orphan*/  ASYNC_WAIT_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASYNC_WAIT_CTX_new () ; 
 int /*<<< orphan*/  ASYNC_cleanup_thread () ; 
 int /*<<< orphan*/  ASYNC_init_thread (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ASYNC_start_job (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * currjob ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  save_current ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int test_ASYNC_get_current_job(void)
{
    ASYNC_JOB *job = NULL;
    int funcret;
    ASYNC_WAIT_CTX *waitctx = NULL;

    currjob = NULL;

    if (       !ASYNC_init_thread(1, 0)
            || (waitctx = ASYNC_WAIT_CTX_new()) == NULL
            || ASYNC_start_job(&job, waitctx, &funcret, save_current, NULL, 0)
                != ASYNC_PAUSE
            || currjob != job
            || ASYNC_start_job(&job, waitctx, &funcret, save_current, NULL, 0)
                != ASYNC_FINISH
            || funcret != 1) {
        fprintf(stderr, "test_ASYNC_get_current_job() failed\n");
        ASYNC_WAIT_CTX_free(waitctx);
        ASYNC_cleanup_thread();
        return 0;
    }

    ASYNC_WAIT_CTX_free(waitctx);
    ASYNC_cleanup_thread();
    return 1;
}