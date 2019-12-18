#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_13__ {TYPE_1__* pFuncsTable; } ;
struct TYPE_12__ {int cStreams; int /*<<< orphan*/  filter; int /*<<< orphan*/ ** ppPins; } ;
struct TYPE_11__ {TYPE_2__* (* pfnBreakConnect ) (TYPE_4__*) ;} ;
typedef  TYPE_2__ ParserImpl ;
typedef  int /*<<< orphan*/  IPin ;
typedef  TYPE_2__* HRESULT ;
typedef  TYPE_4__ BaseOutputPin ;

/* Variables and functions */
 int /*<<< orphan*/  BaseFilterImpl_IncrementPinVersion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IPin_Release (int /*<<< orphan*/ *) ; 
 TYPE_2__* S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 TYPE_2__* stub1 (TYPE_4__*) ; 

__attribute__((used)) static HRESULT Parser_RemoveOutputPins(ParserImpl * This)
{
    /* NOTE: should be in critical section when calling this function */
    HRESULT hr;
    ULONG i;
    IPin ** ppOldPins = This->ppPins;

    TRACE("(%p)\n", This);

    /* reduce the pin array down to 1 (just our input pin) */
    This->ppPins = CoTaskMemAlloc(sizeof(IPin *) * 1);
    memcpy(This->ppPins, ppOldPins, sizeof(IPin *) * 1);

    for (i = 0; i < This->cStreams; i++)
    {
        hr = ((BaseOutputPin *)ppOldPins[i + 1])->pFuncsTable->pfnBreakConnect((BaseOutputPin *)ppOldPins[i + 1]);
        TRACE("Disconnect: %08x\n", hr);
        IPin_Release(ppOldPins[i + 1]);
    }

    BaseFilterImpl_IncrementPinVersion(&This->filter);
    This->cStreams = 0;
    CoTaskMemFree(ppOldPins);

    return S_OK;
}