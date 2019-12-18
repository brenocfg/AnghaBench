#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  IBaseFilter_iface; } ;
struct TYPE_7__ {TYPE_1__ filter; } ;
struct TYPE_6__ {TYPE_3__ Parser; } ;
typedef  TYPE_2__ WAVEParserImpl ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  CLSID_WAVEParser ; 
 TYPE_2__* CoTaskMemAlloc (int) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Parser_Create (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  WAVEParserImpl_seek ; 
 int /*<<< orphan*/  WAVEParser_Cleanup ; 
 int /*<<< orphan*/  WAVEParser_InputPin_PreConnect ; 
 int /*<<< orphan*/  WAVEParser_QueryAccept ; 
 int /*<<< orphan*/  WAVEParser_Sample ; 
 int /*<<< orphan*/  WAVEParser_Vtbl ; 
 int /*<<< orphan*/  WAVEParser_disconnect ; 
 int /*<<< orphan*/  WAVEParser_first_request ; 

HRESULT WAVEParser_create(IUnknown * pUnkOuter, LPVOID * ppv)
{
    HRESULT hr;
    WAVEParserImpl * This;

    TRACE("(%p, %p)\n", pUnkOuter, ppv);

    *ppv = NULL;

    if (pUnkOuter)
        return CLASS_E_NOAGGREGATION;

    /* Note: This memory is managed by the transform filter once created */
    This = CoTaskMemAlloc(sizeof(WAVEParserImpl));

    hr = Parser_Create(&(This->Parser), &WAVEParser_Vtbl, &CLSID_WAVEParser, WAVEParser_Sample, WAVEParser_QueryAccept, WAVEParser_InputPin_PreConnect, WAVEParser_Cleanup, WAVEParser_disconnect, WAVEParser_first_request, NULL, NULL, WAVEParserImpl_seek, NULL);

    if (FAILED(hr))
        return hr;

    *ppv = &This->Parser.filter.IBaseFilter_iface;

    return hr;
}