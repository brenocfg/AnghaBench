#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cs; scalar_t__ remunk_exported; } ;
typedef  int /*<<< orphan*/  STDOBJREF ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IRemUnknown ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ APARTMENT ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IRemUnknown ; 
 int /*<<< orphan*/  IRemUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSHCTX_DIFFERENTMACHINE ; 
 int MSHLFLAGSP_REMUNKNOWN ; 
 int MSHLFLAGS_NORMAL ; 
 scalar_t__ RemUnknown_Construct (int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 scalar_t__ TRUE ; 
 scalar_t__ marshal_object (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

HRESULT start_apartment_remote_unknown(APARTMENT *apt)
{
    IRemUnknown *pRemUnknown;
    HRESULT hr = S_OK;

    EnterCriticalSection(&apt->cs);
    if (!apt->remunk_exported)
    {
        /* create the IRemUnknown object */
        hr = RemUnknown_Construct(&pRemUnknown);
        if (hr == S_OK)
        {
            STDOBJREF stdobjref; /* dummy - not used */
            /* register it with the stub manager */
            hr = marshal_object(apt, &stdobjref, &IID_IRemUnknown, (IUnknown *)pRemUnknown, MSHCTX_DIFFERENTMACHINE, NULL, MSHLFLAGS_NORMAL|MSHLFLAGSP_REMUNKNOWN);
            /* release our reference to the object as the stub manager will manage the life cycle for us */
            IRemUnknown_Release(pRemUnknown);
            if (hr == S_OK)
                apt->remunk_exported = TRUE;
        }
    }
    LeaveCriticalSection(&apt->cs);
    return hr;
}