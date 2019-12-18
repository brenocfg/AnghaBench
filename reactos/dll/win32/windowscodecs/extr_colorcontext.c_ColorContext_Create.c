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
struct TYPE_6__ {int ref; unsigned int exif_color_space; TYPE_1__ IWICColorContext_iface; scalar_t__ profile_len; int /*<<< orphan*/ * profile; scalar_t__ type; } ;
typedef  TYPE_1__ IWICColorContext ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ ColorContext ;

/* Variables and functions */
 int /*<<< orphan*/  ColorContext_Vtbl ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 

HRESULT ColorContext_Create(IWICColorContext **colorcontext)
{
    ColorContext *This;

    if (!colorcontext) return E_INVALIDARG;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(ColorContext));
    if (!This) return E_OUTOFMEMORY;

    This->IWICColorContext_iface.lpVtbl = &ColorContext_Vtbl;
    This->ref = 1;
    This->type = 0;
    This->profile = NULL;
    This->profile_len = 0;
    This->exif_color_space = ~0u;

    *colorcontext = &This->IWICColorContext_iface;

    return S_OK;
}