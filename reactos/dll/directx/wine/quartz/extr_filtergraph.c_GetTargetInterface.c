#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nItfCacheEntries; int nFilters; TYPE_1__* ItfCacheEntries; int /*<<< orphan*/ * ppFiltersInGraph; } ;
struct TYPE_4__ {scalar_t__ riid; scalar_t__ iface; int /*<<< orphan*/  filter; } ;
typedef  scalar_t__ REFIID ;
typedef  scalar_t__ LPVOID ;
typedef  TYPE_2__ IFilterGraphImpl ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_NOINTERFACE ; 
 scalar_t__ E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ IBaseFilter_QueryInterface (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int MAX_ITF_CACHE_ENTRIES ; 
 scalar_t__ S_OK ; 

__attribute__((used)) static HRESULT GetTargetInterface(IFilterGraphImpl* pGraph, REFIID riid, LPVOID* ppvObj)
{
    HRESULT hr = E_NOINTERFACE;
    int i;
    int entry;

    /* Check if the interface type is already registered */
    for (entry = 0; entry < pGraph->nItfCacheEntries; entry++)
        if (riid == pGraph->ItfCacheEntries[entry].riid)
        {
            if (pGraph->ItfCacheEntries[entry].iface)
            {
                /* Return the interface if available */
                *ppvObj = pGraph->ItfCacheEntries[entry].iface;
                return S_OK;
            }
            break;
        }

    if (entry >= MAX_ITF_CACHE_ENTRIES)
    {
        FIXME("Not enough space to store interface in the cache\n");
        return E_OUTOFMEMORY;
    }

    /* Find a filter supporting the requested interface */
    for (i = 0; i < pGraph->nFilters; i++)
    {
        hr = IBaseFilter_QueryInterface(pGraph->ppFiltersInGraph[i], riid, ppvObj);
        if (hr == S_OK)
        {
            pGraph->ItfCacheEntries[entry].riid = riid;
            pGraph->ItfCacheEntries[entry].filter = pGraph->ppFiltersInGraph[i];
            pGraph->ItfCacheEntries[entry].iface = *ppvObj;
            if (entry >= pGraph->nItfCacheEntries)
                pGraph->nItfCacheEntries++;
            return S_OK;
        }
        if (hr != E_NOINTERFACE)
            return hr;
    }

    return hr;
}