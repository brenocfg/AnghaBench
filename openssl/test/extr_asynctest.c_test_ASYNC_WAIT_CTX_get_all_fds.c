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
typedef  scalar_t__ OSSL_ASYNC_FD ;
typedef  int /*<<< orphan*/  ASYNC_WAIT_CTX ;
typedef  int /*<<< orphan*/  ASYNC_JOB ;

/* Variables and functions */
 scalar_t__ ASYNC_FINISH ; 
 scalar_t__ ASYNC_PAUSE ; 
 int /*<<< orphan*/  ASYNC_WAIT_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASYNC_WAIT_CTX_get_all_fds (int /*<<< orphan*/ *,scalar_t__*,size_t*) ; 
 int /*<<< orphan*/  ASYNC_WAIT_CTX_get_changed_fds (int /*<<< orphan*/ *,scalar_t__*,size_t*,scalar_t__*,size_t*) ; 
 int /*<<< orphan*/ * ASYNC_WAIT_CTX_new () ; 
 int /*<<< orphan*/  ASYNC_cleanup_thread () ; 
 int /*<<< orphan*/  ASYNC_init_thread (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ASYNC_start_job (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ MAGIC_WAIT_FD ; 
 scalar_t__ OSSL_BAD_ASYNC_FD ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  waitfd ; 

__attribute__((used)) static int test_ASYNC_WAIT_CTX_get_all_fds(void)
{
    ASYNC_JOB *job = NULL;
    int funcret;
    ASYNC_WAIT_CTX *waitctx = NULL;
    OSSL_ASYNC_FD fd = OSSL_BAD_ASYNC_FD, delfd = OSSL_BAD_ASYNC_FD;
    size_t numfds, numdelfds;

    if (       !ASYNC_init_thread(1, 0)
            || (waitctx = ASYNC_WAIT_CTX_new()) == NULL
               /* On first run we're not expecting any wait fds */
            || ASYNC_start_job(&job, waitctx, &funcret, waitfd, NULL, 0)
                != ASYNC_PAUSE
            || !ASYNC_WAIT_CTX_get_all_fds(waitctx, NULL, &numfds)
            || numfds != 0
            || !ASYNC_WAIT_CTX_get_changed_fds(waitctx, NULL, &numfds, NULL,
                                               &numdelfds)
            || numfds != 0
            || numdelfds != 0
               /* On second run we're expecting one added fd */
            || ASYNC_start_job(&job, waitctx, &funcret, waitfd, NULL, 0)
                != ASYNC_PAUSE
            || !ASYNC_WAIT_CTX_get_all_fds(waitctx, NULL, &numfds)
            || numfds != 1
            || !ASYNC_WAIT_CTX_get_all_fds(waitctx, &fd, &numfds)
            || fd != MAGIC_WAIT_FD
            || (fd = OSSL_BAD_ASYNC_FD, 0) /* Assign to something else */
            || !ASYNC_WAIT_CTX_get_changed_fds(waitctx, NULL, &numfds, NULL,
                                               &numdelfds)
            || numfds != 1
            || numdelfds != 0
            || !ASYNC_WAIT_CTX_get_changed_fds(waitctx, &fd, &numfds, NULL,
                                               &numdelfds)
            || fd != MAGIC_WAIT_FD
               /* On third run we expect one deleted fd */
            || ASYNC_start_job(&job, waitctx, &funcret, waitfd, NULL, 0)
                != ASYNC_PAUSE
            || !ASYNC_WAIT_CTX_get_all_fds(waitctx, NULL, &numfds)
            || numfds != 0
            || !ASYNC_WAIT_CTX_get_changed_fds(waitctx, NULL, &numfds, NULL,
                                               &numdelfds)
            || numfds != 0
            || numdelfds != 1
            || !ASYNC_WAIT_CTX_get_changed_fds(waitctx, NULL, &numfds, &delfd,
                                               &numdelfds)
            || delfd != MAGIC_WAIT_FD
            /* On last run we are not expecting any wait fd */
            || ASYNC_start_job(&job, waitctx, &funcret, waitfd, NULL, 0)
                != ASYNC_FINISH
            || !ASYNC_WAIT_CTX_get_all_fds(waitctx, NULL, &numfds)
            || numfds != 0
            || !ASYNC_WAIT_CTX_get_changed_fds(waitctx, NULL, &numfds, NULL,
                                               &numdelfds)
            || numfds != 0
            || numdelfds != 0
            || funcret != 1) {
        fprintf(stderr, "test_ASYNC_get_wait_fd() failed\n");
        ASYNC_WAIT_CTX_free(waitctx);
        ASYNC_cleanup_thread();
        return 0;
    }

    ASYNC_WAIT_CTX_free(waitctx);
    ASYNC_cleanup_thread();
    return 1;
}