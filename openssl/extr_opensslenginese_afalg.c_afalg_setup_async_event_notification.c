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
struct TYPE_3__ {int efd; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ afalg_aio ;
typedef  int /*<<< orphan*/  ASYNC_WAIT_CTX ;
typedef  int /*<<< orphan*/  ASYNC_JOB ;

/* Variables and functions */
 int /*<<< orphan*/  AFALG_F_AFALG_SETUP_ASYNC_EVENT_NOTIFICATION ; 
 int /*<<< orphan*/  AFALG_R_EVENTFD_FAILED ; 
 int /*<<< orphan*/  AFALGerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ALG_PERR (char*,char*,int) ; 
 int /*<<< orphan*/  ALG_WARN (char*,char*,int) ; 
 int ASYNC_WAIT_CTX_get_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,void**) ; 
 int ASYNC_WAIT_CTX_set_wait_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ASYNC_get_current_job () ; 
 int /*<<< orphan*/ * ASYNC_get_wait_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  MODE_ASYNC ; 
 int /*<<< orphan*/  MODE_SYNC ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  afalg_waitfd_cleanup ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  engine_afalg_id ; 
 void* eventfd (int /*<<< orphan*/ ) ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int afalg_setup_async_event_notification(afalg_aio *aio)
{
    ASYNC_JOB *job;
    ASYNC_WAIT_CTX *waitctx;
    void *custom = NULL;
    int ret;

    if ((job = ASYNC_get_current_job()) != NULL) {
        /* Async mode */
        waitctx = ASYNC_get_wait_ctx(job);
        if (waitctx == NULL) {
            ALG_WARN("%s(%d): ASYNC_get_wait_ctx error", __FILE__, __LINE__);
            return 0;
        }
        /* Get waitfd from ASYNC_WAIT_CTX if it is already set */
        ret = ASYNC_WAIT_CTX_get_fd(waitctx, engine_afalg_id,
                                    &aio->efd, &custom);
        if (ret == 0) {
            /*
             * waitfd is not set in ASYNC_WAIT_CTX, create a new one
             * and set it. efd will be signaled when AIO operation completes
             */
            aio->efd = eventfd(0);
            if (aio->efd == -1) {
                ALG_PERR("%s(%d): Failed to get eventfd : ", __FILE__,
                         __LINE__);
                AFALGerr(AFALG_F_AFALG_SETUP_ASYNC_EVENT_NOTIFICATION,
                         AFALG_R_EVENTFD_FAILED);
                return 0;
            }
            ret = ASYNC_WAIT_CTX_set_wait_fd(waitctx, engine_afalg_id,
                                             aio->efd, custom,
                                             afalg_waitfd_cleanup);
            if (ret == 0) {
                ALG_WARN("%s(%d): Failed to set wait fd", __FILE__, __LINE__);
                close(aio->efd);
                return 0;
            }
            /* make fd non-blocking in async mode */
            if (fcntl(aio->efd, F_SETFL, O_NONBLOCK) != 0) {
                ALG_WARN("%s(%d): Failed to set event fd as NONBLOCKING",
                         __FILE__, __LINE__);
            }
        }
        aio->mode = MODE_ASYNC;
    } else {
        /* Sync mode */
        aio->efd = eventfd(0);
        if (aio->efd == -1) {
            ALG_PERR("%s(%d): Failed to get eventfd : ", __FILE__, __LINE__);
            AFALGerr(AFALG_F_AFALG_SETUP_ASYNC_EVENT_NOTIFICATION,
                     AFALG_R_EVENTFD_FAILED);
            return 0;
        }
        aio->mode = MODE_SYNC;
    }
    return 1;
}