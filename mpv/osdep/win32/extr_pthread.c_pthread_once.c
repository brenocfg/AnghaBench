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
typedef  int /*<<< orphan*/  pthread_once_t ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  InitOnceBeginInitialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitOnceComplete (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort () ; 

int pthread_once(pthread_once_t *once_control, void (*init_routine)(void))
{
    BOOL pending;
    if (!InitOnceBeginInitialize(once_control, 0, &pending, NULL))
        abort();
    if (pending) {
        init_routine();
        InitOnceComplete(once_control, 0, NULL);
    }
    return 0;
}