#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* Flink; } ;
struct TYPE_11__ {TYPE_3__ RecordList; } ;
struct TYPE_9__ {TYPE_1__* Record; } ;
struct TYPE_8__ {int /*<<< orphan*/  pName; } ;
typedef  TYPE_2__* PRESOLVER_CACHE_ENTRY ;
typedef  TYPE_3__* PLIST_ENTRY ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 TYPE_2__* CONTAINING_RECORD (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CacheLink ; 
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ) ; 
 TYPE_5__ DnsCache ; 
 int /*<<< orphan*/  DnsCacheLock () ; 
 int /*<<< orphan*/  DnsCacheUnlock () ; 
 int /*<<< orphan*/  DnsIntCacheRemoveEntryItem (TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RESOLVER_CACHE_ENTRY ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL
DnsIntCacheRemoveEntryByName(LPCWSTR Name)
{
    BOOL Ret = FALSE;
    PRESOLVER_CACHE_ENTRY CacheEntry;
    PLIST_ENTRY NextEntry;

    DPRINT("DnsIntCacheRemoveEntryByName %ws\n", Name);

    /* Lock the cache */
    DnsCacheLock();

    /* Match the Id with all the entries in the List */
    NextEntry = DnsCache.RecordList.Flink;
    while (NextEntry != &DnsCache.RecordList)
    {
        /* Get the Current Entry */
        CacheEntry = CONTAINING_RECORD(NextEntry, RESOLVER_CACHE_ENTRY, CacheLink);

        /* Check if this is the Catalog Entry ID we want */
        if (_wcsicmp(CacheEntry->Record->pName, Name) == 0)
        {
            /* Remove the entry */
            DnsIntCacheRemoveEntryItem(CacheEntry);
            Ret = TRUE;
            break;
        }

        NextEntry = NextEntry->Flink;
    }

    /* Release the cache */
    DnsCacheUnlock();

    /* Return */
    return Ret;
}