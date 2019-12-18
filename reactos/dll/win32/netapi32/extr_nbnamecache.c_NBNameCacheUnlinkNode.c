#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct NBNameCache {int /*<<< orphan*/  heap; } ;
struct TYPE_4__ {struct TYPE_4__* entry; struct TYPE_4__* next; } ;
typedef  TYPE_1__ NBNameCacheNode ;

/* Variables and functions */
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void NBNameCacheUnlinkNode(struct NBNameCache *cache,
 NBNameCacheNode **prev)
{
    if (cache && prev && *prev)
    {
        NBNameCacheNode *next = (*prev)->next;

        HeapFree(cache->heap, 0, (*prev)->entry);
        HeapFree(cache->heap, 0, *prev);
        *prev = next;
    }
}