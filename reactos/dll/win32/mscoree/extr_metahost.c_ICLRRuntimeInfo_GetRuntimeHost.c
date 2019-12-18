#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * lpVtbl; } ;
struct CLRRuntimeInfo {TYPE_1__ ICLRRuntimeInfo_iface; } ;
typedef  int /*<<< orphan*/  RuntimeHost ;
typedef  int /*<<< orphan*/  ICLRRuntimeInfo ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLRRuntimeInfoVtbl ; 
 int /*<<< orphan*/  CLRRuntimeInfo_GetRuntimeHost (struct CLRRuntimeInfo*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct CLRRuntimeInfo* impl_from_ICLRRuntimeInfo (int /*<<< orphan*/ *) ; 

HRESULT ICLRRuntimeInfo_GetRuntimeHost(ICLRRuntimeInfo *iface, RuntimeHost **result)
{
    struct CLRRuntimeInfo *This = impl_from_ICLRRuntimeInfo(iface);

    assert(This->ICLRRuntimeInfo_iface.lpVtbl == &CLRRuntimeInfoVtbl);

    return CLRRuntimeInfo_GetRuntimeHost(This, result);
}