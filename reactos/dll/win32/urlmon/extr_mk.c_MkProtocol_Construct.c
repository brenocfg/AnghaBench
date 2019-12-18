#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int ref; TYPE_3__ IUnknown_outer; int /*<<< orphan*/ * stream; TYPE_3__* outer; TYPE_1__ IInternetProtocolEx_iface; } ;
typedef  TYPE_2__ MkProtocol ;
typedef  TYPE_3__ IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  MkProtocolUnkVtbl ; 
 int /*<<< orphan*/  MkProtocolVtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*,void**) ; 
 int /*<<< orphan*/  URLMON_LockModule () ; 
 TYPE_2__* heap_alloc (int) ; 

HRESULT MkProtocol_Construct(IUnknown *outer, void **ppv)
{
    MkProtocol *ret;

    TRACE("(%p %p)\n", outer, ppv);

    URLMON_LockModule();

    ret = heap_alloc(sizeof(MkProtocol));

    ret->IUnknown_outer.lpVtbl = &MkProtocolUnkVtbl;
    ret->IInternetProtocolEx_iface.lpVtbl = &MkProtocolVtbl;
    ret->ref = 1;
    ret->outer = outer ? outer : &ret->IUnknown_outer;
    ret->stream = NULL;

    /* NOTE:
     * Native returns NULL ppobj and S_OK in CreateInstance if called with IID_IUnknown riid and no outer.
     */
    *ppv = &ret->IUnknown_outer;
    return S_OK;
}