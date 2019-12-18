#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {int /*<<< orphan*/  Record; int /*<<< orphan*/  CacheLink; } ;
typedef  TYPE_1__* PRESOLVER_CACHE_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  DnsFreeRecordList ; 
 int /*<<< orphan*/  DnsRecordListFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  RemoveEntryList (int /*<<< orphan*/ *) ; 

VOID
DnsIntCacheRemoveEntryItem(PRESOLVER_CACHE_ENTRY CacheEntry)
{
    DPRINT("DnsIntCacheRemoveEntryItem %p\n", CacheEntry);

    /* Remove the entry from the list */
    RemoveEntryList(&CacheEntry->CacheLink);
 
    /* Free record */
    DnsRecordListFree(CacheEntry->Record, DnsFreeRecordList);

    /* Delete us */
    HeapFree(GetProcessHeap(), 0, CacheEntry);
}