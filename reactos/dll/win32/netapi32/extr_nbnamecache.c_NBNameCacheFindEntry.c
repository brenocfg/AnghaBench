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
struct NBNameCache {int /*<<< orphan*/  cs; } ;
typedef  char UCHAR ;
struct TYPE_3__ {int /*<<< orphan*/ * entry; } ;
typedef  TYPE_1__ NBNameCacheNode ;
typedef  int /*<<< orphan*/  NBNameCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 TYPE_1__** NBNameCacheWalk (struct NBNameCache*,char const*) ; 
 int NCBNAMSZ ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

const NBNameCacheEntry *NBNameCacheFindEntry(struct NBNameCache *cache,
 const UCHAR name[NCBNAMSZ])
{
    const NBNameCacheEntry *ret;
    UCHAR printName[NCBNAMSZ];

    memcpy(printName, name, NCBNAMSZ - 1);
    printName[NCBNAMSZ - 1] = '\0';
    if (cache)
    {
        NBNameCacheNode **node;

        EnterCriticalSection(&cache->cs);
        node = NBNameCacheWalk(cache, (const char *)name);
        if (node)
            ret = (*node)->entry;
        else
            ret = NULL;
        LeaveCriticalSection(&cache->cs);
    }
    else
        ret = NULL;
    return ret;
}