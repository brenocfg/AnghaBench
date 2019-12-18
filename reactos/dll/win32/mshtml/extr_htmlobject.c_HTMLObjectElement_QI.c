#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  node; } ;
struct TYPE_9__ {TYPE_2__* plugin_host; TYPE_1__ element; } ;
struct TYPE_10__ {int /*<<< orphan*/  IHTMLObjectElement_iface; TYPE_3__ plugin_container; int /*<<< orphan*/  IHTMLObjectElement2_iface; } ;
struct TYPE_8__ {scalar_t__ plugin_unk; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_4__ HTMLObjectElement ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_NOINTERFACE ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ HTMLElement_QI (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IID_HTMLPluginContainer ; 
 int /*<<< orphan*/  IID_IDispatch ; 
 int /*<<< orphan*/  IID_IHTMLObjectElement ; 
 int /*<<< orphan*/  IID_IHTMLObjectElement2 ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IUnknown_QueryInterface (scalar_t__,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_4__*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  debugstr_mshtml_guid (int /*<<< orphan*/ ) ; 
 TYPE_4__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_addref (int /*<<< orphan*/ *) ; 
 scalar_t__ wrap_iface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT HTMLObjectElement_QI(HTMLDOMNode *iface, REFIID riid, void **ppv)
{
    HTMLObjectElement *This = impl_from_HTMLDOMNode(iface);

    TRACE("(%p)->(%s %p)\n", This, debugstr_mshtml_guid(riid), ppv);

    if(IsEqualGUID(&IID_IUnknown, riid)) {
        *ppv = &This->IHTMLObjectElement_iface;
    }else if(IsEqualGUID(&IID_IDispatch, riid)) {
        *ppv = &This->IHTMLObjectElement_iface;
    }else if(IsEqualGUID(&IID_IHTMLObjectElement, riid)) {
        *ppv = &This->IHTMLObjectElement_iface;
    }else if(IsEqualGUID(&IID_IHTMLObjectElement2, riid)) {
        *ppv = &This->IHTMLObjectElement2_iface;
    }else if(IsEqualGUID(&IID_HTMLPluginContainer, riid)) {
        /* Special pseudo-interface returning HTMLPluginContainse struct. */
        *ppv = &This->plugin_container;
        node_addref(&This->plugin_container.element.node);
        return S_OK;
    }else {
        HRESULT hres;

        hres = HTMLElement_QI(&This->plugin_container.element.node, riid, ppv);
        if(hres == E_NOINTERFACE && This->plugin_container.plugin_host && This->plugin_container.plugin_host->plugin_unk) {
            IUnknown *plugin_iface, *ret;

            hres = IUnknown_QueryInterface(This->plugin_container.plugin_host->plugin_unk, riid, (void**)&plugin_iface);
            if(hres == S_OK) {
                hres = wrap_iface(plugin_iface, (IUnknown*)&This->IHTMLObjectElement_iface, &ret);
                IUnknown_Release(plugin_iface);
                if(FAILED(hres))
                    return hres;

                TRACE("returning plugin iface %p wrapped to %p\n", plugin_iface, ret);
                *ppv = ret;
                return S_OK;
            }
        }

        return hres;
    }

    IUnknown_AddRef((IUnknown*)*ppv);
    return S_OK;
}