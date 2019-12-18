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
struct TYPE_3__ {scalar_t__ tag; } ;
typedef  TYPE_1__ NETDATA_THREAD ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gettid () ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  pthread_set_name_np (int /*<<< orphan*/ ,char*) ; 
 int pthread_setname_np (char*,...) ; 
 int /*<<< orphan*/  strncpyz (char*,scalar_t__,int) ; 

__attribute__((used)) static void thread_set_name(NETDATA_THREAD *nt) {

    if (nt->tag) {
        int ret = 0;

        // Name is limited to 16 chars
        char threadname[16];
        strncpyz(threadname, nt->tag, 15);

#if defined(__FreeBSD__)
        pthread_set_name_np(pthread_self(), threadname);
#elif defined(__APPLE__)
        ret = pthread_setname_np(threadname);
#else
        ret = pthread_setname_np(pthread_self(), threadname);
#endif

        if (ret != 0)
            error("cannot set pthread name of %d to %s. ErrCode: %d", gettid(), threadname, ret);
        else
            info("set name of thread %d to %s", gettid(), threadname);

    }
}