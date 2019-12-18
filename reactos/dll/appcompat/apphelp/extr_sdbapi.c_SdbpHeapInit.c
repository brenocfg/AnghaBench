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

/* Variables and functions */
 int /*<<< orphan*/  HEAP_GROWABLE ; 
 int /*<<< orphan*/  RtlCreateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SdbpDebugHeapInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_Heap ; 

void SdbpHeapInit(void)
{
    g_Heap = RtlCreateHeap(HEAP_GROWABLE, NULL, 0, 0x10000, NULL, NULL);
#if SDBAPI_DEBUG_ALLOC
    SdbpDebugHeapInit(g_Heap);
#endif
}