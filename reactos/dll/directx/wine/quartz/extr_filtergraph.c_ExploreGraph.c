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
typedef  int /*<<< orphan*/  (* fnFoundFilter ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
typedef  scalar_t__ ULONG ;
struct TYPE_6__ {int /*<<< orphan*/  nRenderers; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pFilter; } ;
typedef  TYPE_1__ PIN_INFO ;
typedef  int /*<<< orphan*/  IPin ;
typedef  TYPE_2__ IFilterGraphImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GetInternalConnections (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ***,scalar_t__*) ; 
 int /*<<< orphan*/  IBaseFilter_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPin_ConnectedTo (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IPin_QueryPinInfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  IPin_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 

__attribute__((used)) static HRESULT ExploreGraph(IFilterGraphImpl* pGraph, IPin* pOutputPin, fnFoundFilter FoundFilter, DWORD_PTR data)
{
    HRESULT hr;
    IPin* pInputPin;
    IPin** ppPins;
    ULONG nb;
    ULONG i;
    PIN_INFO PinInfo;

    TRACE("%p %p\n", pGraph, pOutputPin);
    PinInfo.pFilter = NULL;

    hr = IPin_ConnectedTo(pOutputPin, &pInputPin);

    if (SUCCEEDED(hr))
    {
        hr = IPin_QueryPinInfo(pInputPin, &PinInfo);
        if (SUCCEEDED(hr))
            hr = GetInternalConnections(PinInfo.pFilter, pInputPin, &ppPins, &nb);
        IPin_Release(pInputPin);
    }

    if (SUCCEEDED(hr))
    {
        if (nb == 0)
        {
            TRACE("Reached a renderer\n");
            /* Count renderers for end of stream notification */
            pGraph->nRenderers++;
        }
        else
        {
            for(i = 0; i < nb; i++)
            {
                /* Explore the graph downstream from this pin
                 * FIXME: We should prevent exploring from a pin more than once. This can happens when
                 * several input pins are connected to the same output (a MUX for instance). */
                ExploreGraph(pGraph, ppPins[i], FoundFilter, data);
                IPin_Release(ppPins[i]);
            }

            CoTaskMemFree(ppPins);
        }
        TRACE("Doing stuff with filter %p\n", PinInfo.pFilter);

        FoundFilter(PinInfo.pFilter, data);
    }

    if (PinInfo.pFilter) IBaseFilter_Release(PinInfo.pFilter);
    return hr;
}