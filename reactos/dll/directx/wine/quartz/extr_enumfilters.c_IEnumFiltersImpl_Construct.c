#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int refCount; TYPE_2__ IEnumFilters_iface; int /*<<< orphan*/  Version; int /*<<< orphan*/ * pVersionSource; int /*<<< orphan*/ *** pppFilters; int /*<<< orphan*/ * pNumFilters; scalar_t__ uIndex; } ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  IGraphVersion ;
typedef  TYPE_1__ IEnumFiltersImpl ;
typedef  TYPE_2__ IEnumFilters ;
typedef  int /*<<< orphan*/  IBaseFilter ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 TYPE_1__* CoTaskMemAlloc (int) ; 
 scalar_t__ E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IEnumFiltersImpl_Vtbl ; 
 int /*<<< orphan*/  IGraphVersion_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IGraphVersion_QueryVersion (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ***,int /*<<< orphan*/ *,TYPE_2__**) ; 

HRESULT IEnumFiltersImpl_Construct(IGraphVersion * pVersionSource, IBaseFilter *** pppFilters, ULONG * pNumFilters, IEnumFilters ** ppEnum)
{
    /* Note: The incoming IBaseFilter interfaces are not AddRef'd here as in Windows,
     * they should have been previously AddRef'd. */
    IEnumFiltersImpl * pEnumFilters = CoTaskMemAlloc(sizeof(IEnumFiltersImpl));
    HRESULT hr;
    LONG currentVersion;

    TRACE("(%p, %p, %p)\n", pppFilters, pNumFilters, ppEnum);

    *ppEnum = NULL;

    if (!pEnumFilters)
    {
        return E_OUTOFMEMORY;
    }

    pEnumFilters->IEnumFilters_iface.lpVtbl = &IEnumFiltersImpl_Vtbl;
    pEnumFilters->refCount = 1;
    pEnumFilters->uIndex = 0;
    pEnumFilters->pNumFilters = pNumFilters;
    pEnumFilters->pppFilters = pppFilters;
    IGraphVersion_AddRef(pVersionSource);
    pEnumFilters->pVersionSource = pVersionSource;

    /* Store the current version of the graph */
    hr = IGraphVersion_QueryVersion(pVersionSource, &currentVersion);
    pEnumFilters->Version = (hr==S_OK) ? currentVersion : 0;

    *ppEnum = &pEnumFilters->IEnumFilters_iface;
    return S_OK;
}