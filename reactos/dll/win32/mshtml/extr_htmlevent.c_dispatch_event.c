#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t eventid_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VARIANT_BOOL ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_11__ {int flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  nsnode; int /*<<< orphan*/  doc; } ;
struct TYPE_9__ {int /*<<< orphan*/  IHTMLEventObj_iface; } ;
typedef  int /*<<< orphan*/  IHTMLEventObj ;
typedef  TYPE_1__ HTMLEventObj ;
typedef  TYPE_2__ HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 size_t EVENTID_LAST ; 
 int EVENT_DEFAULTLISTENER ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  IDispatch_QueryInterface (scalar_t__,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLEventObj_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHTMLEventObj ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VARIANT_TRUE ; 
 scalar_t__ VT_DISPATCH ; 
 scalar_t__ VT_EMPTY ; 
 scalar_t__ VT_ERROR ; 
 scalar_t__ V_DISPATCH (int /*<<< orphan*/ *) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 size_t attr_to_eid (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 TYPE_7__* event_info ; 
 int /*<<< orphan*/  fire_event (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fire_event_obj (int /*<<< orphan*/ ,size_t,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_event_info (TYPE_1__*,TYPE_2__*,size_t,int /*<<< orphan*/ *) ; 
 TYPE_1__* unsafe_impl_from_IHTMLEventObj (int /*<<< orphan*/ *) ; 

HRESULT dispatch_event(HTMLDOMNode *node, const WCHAR *event_name, VARIANT *event_var, VARIANT_BOOL *cancelled)
{
    HTMLEventObj *event_obj = NULL;
    eventid_t eid;
    HRESULT hres;

    eid = attr_to_eid(event_name);
    if(eid == EVENTID_LAST) {
        WARN("unknown event %s\n", debugstr_w(event_name));
        return E_INVALIDARG;
    }

    if(event_var && V_VT(event_var) != VT_EMPTY && V_VT(event_var) != VT_ERROR) {
        if(V_VT(event_var) != VT_DISPATCH) {
            FIXME("event_var %s not supported\n", debugstr_variant(event_var));
            return E_NOTIMPL;
        }

        if(V_DISPATCH(event_var)) {
            IHTMLEventObj *event_iface;

            hres = IDispatch_QueryInterface(V_DISPATCH(event_var), &IID_IHTMLEventObj, (void**)&event_iface);
            if(FAILED(hres)) {
                FIXME("No IHTMLEventObj iface\n");
                return hres;
            }

            event_obj = unsafe_impl_from_IHTMLEventObj(event_iface);
            if(!event_obj) {
                ERR("Not our IHTMLEventObj?\n");
                IHTMLEventObj_Release(event_iface);
                return E_FAIL;
            }
        }
    }

    if(event_obj) {
        hres = set_event_info(event_obj, node, eid, NULL);
        if(SUCCEEDED(hres))
            fire_event_obj(node->doc, eid, event_obj, node->nsnode, NULL);

        IHTMLEventObj_Release(&event_obj->IHTMLEventObj_iface);
        if(FAILED(hres))
            return hres;
    }else {
        if(!(event_info[eid].flags & EVENT_DEFAULTLISTENER)) {
            FIXME("not EVENT_DEFAULTEVENTHANDLER\n");
            return E_NOTIMPL;
        }

        fire_event(node->doc, eid, TRUE, node->nsnode, NULL, NULL);
    }

    *cancelled = VARIANT_TRUE; /* FIXME */
    return S_OK;
}