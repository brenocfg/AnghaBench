#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int ref; TYPE_1__ IWICColorTransform_iface; int /*<<< orphan*/ * dst; } ;
typedef  TYPE_1__ IWICColorTransform ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ ColorTransform ;

/* Variables and functions */
 int /*<<< orphan*/  ColorTransform_Vtbl ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 

HRESULT ColorTransform_Create(IWICColorTransform **colortransform)
{
    ColorTransform *This;

    if (!colortransform) return E_INVALIDARG;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(ColorTransform));
    if (!This) return E_OUTOFMEMORY;

    This->IWICColorTransform_iface.lpVtbl = &ColorTransform_Vtbl;
    This->ref = 1;
    This->dst = NULL;

    *colortransform = &This->IWICColorTransform_iface;

    return S_OK;
}