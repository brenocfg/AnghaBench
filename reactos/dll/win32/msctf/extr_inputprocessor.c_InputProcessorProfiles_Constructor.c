#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int refCount; TYPE_3__ ITfInputProcessorProfiles_iface; int /*<<< orphan*/  LanguageProfileNotifySink; int /*<<< orphan*/  currentLanguage; TYPE_2__ ITfInputProcessorProfileMgr_iface; TYPE_1__ ITfSource_iface; } ;
typedef  TYPE_4__ InputProcessorProfiles ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetUserDefaultLCID () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InputProcessorProfileMgrVtbl ; 
 int /*<<< orphan*/  InputProcessorProfilesSourceVtbl ; 
 int /*<<< orphan*/  InputProcessorProfilesVtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

HRESULT InputProcessorProfiles_Constructor(IUnknown *pUnkOuter, IUnknown **ppOut)
{
    InputProcessorProfiles *This;
    if (pUnkOuter)
        return CLASS_E_NOAGGREGATION;

    This = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(InputProcessorProfiles));
    if (This == NULL)
        return E_OUTOFMEMORY;

    This->ITfInputProcessorProfiles_iface.lpVtbl= &InputProcessorProfilesVtbl;
    This->ITfSource_iface.lpVtbl = &InputProcessorProfilesSourceVtbl;
    This->ITfInputProcessorProfileMgr_iface.lpVtbl = &InputProcessorProfileMgrVtbl;
    This->refCount = 1;
    This->currentLanguage = GetUserDefaultLCID();

    list_init(&This->LanguageProfileNotifySink);

    *ppOut = (IUnknown *)&This->ITfInputProcessorProfiles_iface;
    TRACE("returning %p\n", *ppOut);
    return S_OK;
}