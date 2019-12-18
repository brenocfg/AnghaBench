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
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_2__ IWshEnvironment_iface; int /*<<< orphan*/  classinfo; } ;
typedef  TYPE_1__ WshEnvironment ;
typedef  TYPE_2__ IWshEnvironment ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IID_IWshEnvironment ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WshEnvironmentVtbl ; 
 TYPE_1__* heap_alloc (int) ; 
 int /*<<< orphan*/  init_classinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT WshEnvironment_Create(IWshEnvironment **env)
{
    WshEnvironment *This;

    This = heap_alloc(sizeof(*This));
    if (!This) return E_OUTOFMEMORY;

    This->IWshEnvironment_iface.lpVtbl = &WshEnvironmentVtbl;
    This->ref = 1;

    init_classinfo(&IID_IWshEnvironment, (IUnknown *)&This->IWshEnvironment_iface, &This->classinfo);
    *env = &This->IWshEnvironment_iface;

    return S_OK;
}