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
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int refs; TYPE_2__ INetFwProfile_iface; } ;
typedef  TYPE_1__ fw_profile ;
typedef  TYPE_2__* LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,...) ; 
 int /*<<< orphan*/  fw_profile_vtbl ; 

HRESULT NetFwProfile_create( IUnknown *pUnkOuter, LPVOID *ppObj )
{
    fw_profile *fp;

    TRACE("(%p,%p)\n", pUnkOuter, ppObj);

    fp = HeapAlloc( GetProcessHeap(), 0, sizeof(*fp) );
    if (!fp) return E_OUTOFMEMORY;

    fp->INetFwProfile_iface.lpVtbl = &fw_profile_vtbl;
    fp->refs = 1;

    *ppObj = &fp->INetFwProfile_iface;

    TRACE("returning iface %p\n", *ppObj);
    return S_OK;
}