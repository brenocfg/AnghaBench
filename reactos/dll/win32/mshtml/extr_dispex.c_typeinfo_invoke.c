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
struct TYPE_5__ {size_t tid; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ func_info_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_6__ {int /*<<< orphan*/  outer; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  EXCEPINFO ;
typedef  TYPE_2__ DispatchEx ;
typedef  int /*<<< orphan*/  DISPPARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITypeInfo_Invoke (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_mshtml_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_typeinfo (size_t,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * tid_ids ; 

__attribute__((used)) static HRESULT typeinfo_invoke(DispatchEx *This, func_info_t *func, WORD flags, DISPPARAMS *dp, VARIANT *res,
        EXCEPINFO *ei)
{
    ITypeInfo *ti;
    IUnknown *unk;
    UINT argerr=0;
    HRESULT hres;

    hres = get_typeinfo(func->tid, &ti);
    if(FAILED(hres)) {
        ERR("Could not get type info: %08x\n", hres);
        return hres;
    }

    hres = IUnknown_QueryInterface(This->outer, tid_ids[func->tid], (void**)&unk);
    if(FAILED(hres)) {
        ERR("Could not get iface %s: %08x\n", debugstr_mshtml_guid(tid_ids[func->tid]), hres);
        return E_FAIL;
    }

    hres = ITypeInfo_Invoke(ti, unk, func->id, flags, dp, res, ei, &argerr);

    IUnknown_Release(unk);
    return hres;
}