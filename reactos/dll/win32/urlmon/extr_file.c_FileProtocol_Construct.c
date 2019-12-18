#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int ref; TYPE_3__ IUnknown_outer; int /*<<< orphan*/ * outer; scalar_t__ priority; int /*<<< orphan*/  file; TYPE_2__ IInternetPriority_iface; TYPE_1__ IInternetProtocolEx_iface; } ;
typedef  TYPE_3__* LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_4__ FileProtocol ;

/* Variables and functions */
 int /*<<< orphan*/  FilePriorityVtbl ; 
 int /*<<< orphan*/  FileProtocolExVtbl ; 
 int /*<<< orphan*/  FileProtocolUnkVtbl ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  URLMON_LockModule () ; 
 TYPE_4__* heap_alloc (int) ; 

HRESULT FileProtocol_Construct(IUnknown *outer, LPVOID *ppobj)
{
    FileProtocol *ret;

    TRACE("(%p %p)\n", outer, ppobj);

    URLMON_LockModule();

    ret = heap_alloc(sizeof(FileProtocol));

    ret->IUnknown_outer.lpVtbl = &FileProtocolUnkVtbl;
    ret->IInternetProtocolEx_iface.lpVtbl = &FileProtocolExVtbl;
    ret->IInternetPriority_iface.lpVtbl = &FilePriorityVtbl;
    ret->file = INVALID_HANDLE_VALUE;
    ret->priority = 0;
    ret->ref = 1;
    ret->outer = outer ? outer : (IUnknown*)&ret->IUnknown_outer;

    *ppobj = &ret->IUnknown_outer;
    return S_OK;
}