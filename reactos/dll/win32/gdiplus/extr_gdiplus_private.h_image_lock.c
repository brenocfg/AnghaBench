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
struct TYPE_3__ {int /*<<< orphan*/  busy; } ;
typedef  scalar_t__ LONG ;
typedef  TYPE_1__ GpImage ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ GetCurrentThreadId () ; 
 scalar_t__ InterlockedCompareExchange (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline BOOL image_lock(GpImage *image, BOOL *unlock)
{
    LONG tid = GetCurrentThreadId(), owner_tid;
    owner_tid = InterlockedCompareExchange(&image->busy, tid, 0);
    *unlock = !owner_tid;
    return !owner_tid || owner_tid==tid;
}