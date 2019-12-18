#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsAString ;
struct TYPE_16__ {int /*<<< orphan*/  IDispatchEx_iface; } ;
struct TYPE_21__ {TYPE_3__ dispex; } ;
struct TYPE_14__ {TYPE_8__ event_target; } ;
struct TYPE_20__ {TYPE_2__* window; int /*<<< orphan*/  basedoc; TYPE_1__ node; } ;
struct TYPE_17__ {TYPE_8__ event_target; } ;
struct TYPE_19__ {TYPE_4__ node; } ;
struct TYPE_18__ {int /*<<< orphan*/  nsscript; } ;
struct TYPE_15__ {TYPE_8__ event_target; } ;
typedef  int /*<<< orphan*/  PRUnichar ;
typedef  TYPE_5__ HTMLScriptElement ;
typedef  TYPE_6__ HTMLElement ;
typedef  TYPE_7__ HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_8__ EventTarget ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IDispatchEx_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  documentW ; 
 int /*<<< orphan*/  get_doc_elem_by_id (TYPE_7__*,int /*<<< orphan*/  const*,TYPE_6__**) ; 
 int /*<<< orphan*/  htmldoc_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLScriptElement_GetHtmlFor (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  windowW ; 

__attribute__((used)) static EventTarget *find_event_target(HTMLDocumentNode *doc, HTMLScriptElement *script_elem)
{
    EventTarget *event_target = NULL;
    const PRUnichar *target_id;
    nsAString target_id_str;
    nsresult nsres;
    HRESULT hres;

    nsAString_Init(&target_id_str, NULL);
    nsres = nsIDOMHTMLScriptElement_GetHtmlFor(script_elem->nsscript, &target_id_str);
    if(NS_FAILED(nsres)) {
        ERR("GetScriptFor failed: %08x\n", nsres);
        nsAString_Finish(&target_id_str);
        return NULL;
    }

    nsAString_GetData(&target_id_str, &target_id);
    if(!*target_id) {
        FIXME("Empty for attribute\n");
    }else if(!strcmpW(target_id, documentW)) {
        event_target = &doc->node.event_target;
        htmldoc_addref(&doc->basedoc);
    }else if(!strcmpW(target_id, windowW)) {
        if(doc->window) {
            event_target = &doc->window->event_target;
            IDispatchEx_AddRef(&event_target->dispex.IDispatchEx_iface);
        }
    }else {
        HTMLElement *target_elem;

        hres = get_doc_elem_by_id(doc, target_id, &target_elem);
        if(SUCCEEDED(hres) && target_elem) {
            event_target = &target_elem->node.event_target;
        }
    }

    nsAString_Finish(&target_id_str);
    return event_target;
}