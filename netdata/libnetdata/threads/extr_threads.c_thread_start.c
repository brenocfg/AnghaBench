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
struct TYPE_3__ {int options; int /*<<< orphan*/  arg; void* (* start_routine ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ NETDATA_THREAD ;

/* Variables and functions */
 int NETDATA_THREAD_OPTION_DONT_LOG_STARTUP ; 
 int /*<<< orphan*/  PTHREAD_CANCEL_DEFERRED ; 
 int /*<<< orphan*/  PTHREAD_CANCEL_ENABLE ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gettid () ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* netdata_thread ; 
 int /*<<< orphan*/  pthread_cleanup_pop (int) ; 
 int /*<<< orphan*/  pthread_cleanup_push (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_setcancelstate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_setcanceltype (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_cleanup ; 
 int /*<<< orphan*/  thread_set_name (void*) ; 

__attribute__((used)) static void *thread_start(void *ptr) {
    netdata_thread = (NETDATA_THREAD *)ptr;

    if(!(netdata_thread->options & NETDATA_THREAD_OPTION_DONT_LOG_STARTUP))
        info("thread created with task id %d", gettid());

    if(pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL) != 0)
        error("cannot set pthread cancel type to DEFERRED.");

    if(pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL) != 0)
        error("cannot set pthread cancel state to ENABLE.");

    thread_set_name(ptr);

    void *ret = NULL;
    pthread_cleanup_push(thread_cleanup, ptr);
            ret = netdata_thread->start_routine(netdata_thread->arg);
    pthread_cleanup_pop(1);

    return ret;
}