#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ nsresult ;
typedef  int /*<<< orphan*/  nsIDOMNodeList ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIDOMHTMLScriptElement ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT32 ;
struct TYPE_20__ {int /*<<< orphan*/  IDispatchEx_iface; } ;
struct TYPE_25__ {TYPE_1__ dispex; } ;
struct TYPE_24__ {int /*<<< orphan*/  nsdoc; } ;
struct TYPE_21__ {int /*<<< orphan*/  node; } ;
struct TYPE_23__ {TYPE_2__ element; } ;
struct TYPE_22__ {int /*<<< orphan*/  IHTMLScriptElement_iface; } ;
typedef  char PRUnichar ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  TYPE_3__ HTMLScriptElement ;
typedef  TYPE_4__ HTMLPluginContainer ;
typedef  TYPE_5__ HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_6__ EventTarget ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__,...) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDispatchEx_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDispatchEx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLScriptElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_HTMLPluginContainer ; 
 int /*<<< orphan*/  IID_nsIDOMHTMLScriptElement ; 
 scalar_t__ NS_FAILED (scalar_t__) ; 
 scalar_t__ NS_OK ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_5__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bind_activex_event (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bind_target_event (TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_6__* find_event_target (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_InitDepend (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ nsIDOMHTMLDocument_QuerySelectorAll (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ nsIDOMNodeList_GetLength (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ nsIDOMNodeList_Item (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNodeList_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ nsIDOMNode_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * parse_event_elem (TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  script_elem_from_nsscript (TYPE_5__*,int /*<<< orphan*/ *,TYPE_3__**) ; 

void bind_event_scripts(HTMLDocumentNode *doc)
{
    HTMLPluginContainer *plugin_container;
    nsIDOMHTMLScriptElement *nsscript;
    HTMLScriptElement *script_elem;
    EventTarget *event_target;
    nsIDOMNodeList *node_list;
    nsIDOMNode *script_node;
    nsAString selector_str;
    IDispatch *event_disp;
    UINT32 length, i;
    WCHAR *event;
    nsresult nsres;
    HRESULT hres;

    static const PRUnichar selectorW[] = {'s','c','r','i','p','t','[','e','v','e','n','t',']',0};

    TRACE("%p\n", doc);

    if(!doc->nsdoc)
        return;

    nsAString_InitDepend(&selector_str, selectorW);
    nsres = nsIDOMHTMLDocument_QuerySelectorAll(doc->nsdoc, &selector_str, &node_list);
    nsAString_Finish(&selector_str);
    if(NS_FAILED(nsres)) {
        ERR("QuerySelectorAll failed: %08x\n", nsres);
        return;
    }

    if(!node_list)
        return;

    nsres = nsIDOMNodeList_GetLength(node_list, &length);
    assert(nsres == NS_OK);

    for(i=0; i < length; i++) {
        nsres = nsIDOMNodeList_Item(node_list, i, &script_node);
        if(NS_FAILED(nsres) || !script_node) {
            ERR("Item(%d) failed: %08x\n", i, nsres);
            continue;
        }

        nsres = nsIDOMNode_QueryInterface(script_node, &IID_nsIDOMHTMLScriptElement, (void**)&nsscript);
        assert(nsres == NS_OK);
        nsIDOMNode_Release(script_node);

        hres = script_elem_from_nsscript(doc, nsscript, &script_elem);
        if(FAILED(hres))
            continue;

        event_disp = parse_event_elem(doc, script_elem, &event);
        if(event_disp) {
            event_target = find_event_target(doc, script_elem);
            if(event_target) {
                hres = IDispatchEx_QueryInterface(&event_target->dispex.IDispatchEx_iface, &IID_HTMLPluginContainer,
                        (void**)&plugin_container);
                if(SUCCEEDED(hres))
                    bind_activex_event(doc, plugin_container, event, event_disp);
                else
                    bind_target_event(doc, event_target, event, event_disp);

                IDispatchEx_Release(&event_target->dispex.IDispatchEx_iface);
                if(plugin_container)
                    node_release(&plugin_container->element.node);
            }

            heap_free(event);
            IDispatch_Release(event_disp);
        }

        IHTMLScriptElement_Release(&script_elem->IHTMLScriptElement_iface);
    }

    nsIDOMNodeList_Release(node_list);
}