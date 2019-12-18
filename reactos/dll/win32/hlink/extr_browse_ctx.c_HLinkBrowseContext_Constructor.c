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
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; int /*<<< orphan*/ * current; int /*<<< orphan*/  links; TYPE_1__ IHlinkBrowseContext_iface; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_2__ HlinkBCImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 TYPE_2__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  hlvt ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

HRESULT HLinkBrowseContext_Constructor(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
    HlinkBCImpl * hl;

    TRACE("unkOut=%p riid=%s\n", pUnkOuter, debugstr_guid(riid));
    *ppv = NULL;

    if (pUnkOuter)
        return CLASS_E_NOAGGREGATION;

    hl = heap_alloc_zero(sizeof(HlinkBCImpl));
    if (!hl)
        return E_OUTOFMEMORY;

    hl->ref = 1;
    hl->IHlinkBrowseContext_iface.lpVtbl = &hlvt;
    list_init(&hl->links);
    hl->current = NULL;

    *ppv = hl;
    return S_OK;
}