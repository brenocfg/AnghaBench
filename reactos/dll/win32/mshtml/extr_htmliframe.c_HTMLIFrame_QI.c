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
struct TYPE_4__ {int /*<<< orphan*/  framebase; int /*<<< orphan*/  IHTMLIFrameElement3_iface; int /*<<< orphan*/  IHTMLIFrameElement2_iface; int /*<<< orphan*/  IHTMLIFrameElement_iface; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_1__ HTMLIFrame ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  HTMLFrameBase_QI (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IID_IHTMLIFrameElement ; 
 int /*<<< orphan*/  IID_IHTMLIFrameElement2 ; 
 int /*<<< orphan*/  IID_IHTMLIFrameElement3 ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,void**) ; 
 TYPE_1__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT HTMLIFrame_QI(HTMLDOMNode *iface, REFIID riid, void **ppv)
{
    HTMLIFrame *This = impl_from_HTMLDOMNode(iface);

    if(IsEqualGUID(&IID_IHTMLIFrameElement, riid)) {
        TRACE("(%p)->(IID_IHTMLIFrameElement %p)\n", This, ppv);
        *ppv = &This->IHTMLIFrameElement_iface;
    }else if(IsEqualGUID(&IID_IHTMLIFrameElement2, riid)) {
        TRACE("(%p)->(IID_IHTMLIFrameElement2 %p)\n", This, ppv);
        *ppv = &This->IHTMLIFrameElement2_iface;
    }else if(IsEqualGUID(&IID_IHTMLIFrameElement3, riid)) {
        TRACE("(%p)->(IID_IHTMLIFrameElement3 %p)\n", This, ppv);
        *ppv = &This->IHTMLIFrameElement3_iface;
    }else {
        return HTMLFrameBase_QI(&This->framebase, riid, ppv);
    }

    IUnknown_AddRef((IUnknown*)*ppv);
    return S_OK;
}