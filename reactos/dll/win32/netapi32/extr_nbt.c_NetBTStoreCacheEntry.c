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
struct NBNameCache {int dummy; } ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  NBNameCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ NBNameCacheAddEntry (struct NBNameCache*,int /*<<< orphan*/ *) ; 
 struct NBNameCache* NBNameCacheCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NRC_BADDR ; 
 int /*<<< orphan*/  NRC_GOODRET ; 
 int /*<<< orphan*/  NRC_OSRESNOTAV ; 
 int /*<<< orphan*/  gCacheTimeout ; 

__attribute__((used)) static UCHAR NetBTStoreCacheEntry(struct NBNameCache **nameCache,
 NBNameCacheEntry *cacheEntry)
{
    UCHAR ret;

    if (!nameCache) return NRC_BADDR;
    if (!cacheEntry) return NRC_BADDR;

    if (!*nameCache)
        *nameCache = NBNameCacheCreate(GetProcessHeap(), gCacheTimeout);
    if (*nameCache)
        ret = NBNameCacheAddEntry(*nameCache, cacheEntry)
         ?  NRC_GOODRET : NRC_OSRESNOTAV;
    else
    {
        HeapFree(GetProcessHeap(), 0, cacheEntry);
        ret = NRC_OSRESNOTAV;
    }
    return ret;
}