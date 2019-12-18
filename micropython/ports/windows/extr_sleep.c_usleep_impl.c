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
typedef  int __int64 ;
struct TYPE_3__ {int QuadPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  INFINITE ; 
 int LLONG_MAX ; 
 scalar_t__ SetWaitableTimer (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * waitTimer ; 

int usleep_impl(__int64 usec) {
    if (waitTimer == NULL) {
        errno = EAGAIN;
        return -1;
    }
    if (usec < 0 || usec > LLONG_MAX / 10) {
        errno = EINVAL;
        return -1;
    }

    LARGE_INTEGER ft;
    ft.QuadPart = -10 * usec; // 100 nanosecond interval, negative value = relative time
    if (SetWaitableTimer(waitTimer, &ft, 0, NULL, NULL, 0) == 0) {
        errno = EINVAL;
        return -1;
    }
    if (WaitForSingleObject(waitTimer, INFINITE) != WAIT_OBJECT_0) {
        errno = EAGAIN;
        return -1;
    }
    return 0;
}