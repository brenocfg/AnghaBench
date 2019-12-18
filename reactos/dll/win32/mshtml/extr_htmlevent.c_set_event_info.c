#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMEvent ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  int eventid_t ;
struct TYPE_10__ {size_t type; } ;
struct TYPE_9__ {int /*<<< orphan*/  IHTMLDOMNode_iface; TYPE_1__* doc; } ;
struct TYPE_8__ {TYPE_3__* target; int /*<<< orphan*/ * nsevent; TYPE_6__* type; } ;
struct TYPE_7__ {int /*<<< orphan*/  nsdoc; } ;
typedef  TYPE_2__ HTMLEventObj ;
typedef  TYPE_3__ HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  IHTMLDOMNode_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_6__* event_info ; 
 scalar_t__* event_types ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_InitDepend (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  nsIDOMEvent_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLDocument_CreateEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT set_event_info(HTMLEventObj *event, HTMLDOMNode *target, eventid_t eid, nsIDOMEvent *nsevent)
{
    event->type = event_info+eid;
    event->nsevent = nsevent;

    if(nsevent) {
        nsIDOMEvent_AddRef(nsevent);
    }else if(event_types[event_info[eid].type]) {
        nsAString type_str;
        nsresult nsres;

        nsAString_InitDepend(&type_str, event_types[event_info[eid].type]);
        nsres = nsIDOMHTMLDocument_CreateEvent(target->doc->nsdoc, &type_str, &event->nsevent);
        nsAString_Finish(&type_str);
        if(NS_FAILED(nsres)) {
            ERR("Could not create event: %08x\n", nsres);
            return E_FAIL;
        }
    }

    event->target = target;
    if(target)
        IHTMLDOMNode_AddRef(&target->IHTMLDOMNode_iface);
    return S_OK;
}