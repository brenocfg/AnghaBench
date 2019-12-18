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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_gettid ; 
 int /*<<< orphan*/  pthread_getthreadid_np () ; 
 int /*<<< orphan*/  pthread_self ; 
 int /*<<< orphan*/  pthread_threadid_np (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ) ; 

pid_t gettid(void) {
#ifdef __FreeBSD__

    return (pid_t)pthread_getthreadid_np();

#elif defined(__APPLE__)

    #if (defined __MAC_OS_X_VERSION_MIN_REQUIRED && __MAC_OS_X_VERSION_MIN_REQUIRED >= 1060)
        uint64_t curthreadid;
        pthread_threadid_np(NULL, &curthreadid);
        return (pid_t)curthreadid;
    #else /* __MAC_OS_X_VERSION_MIN_REQUIRED */
        return (pid_t)pthread_self;
    #endif /* __MAC_OS_X_VERSION_MIN_REQUIRED */

#else /* __APPLE__*/

    return (pid_t)syscall(SYS_gettid);

#endif /* __FreeBSD__, __APPLE__*/
}