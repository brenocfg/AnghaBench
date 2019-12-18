#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMKeyEvent ;
typedef  int /*<<< orphan*/  nsIDOMEvent ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_4__ {int /*<<< orphan*/  nsnode; int /*<<< orphan*/  doc; } ;
struct TYPE_5__ {TYPE_1__ node; } ;
typedef  TYPE_2__ HTMLElement ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTID_HELP ; 
#define  EVENTID_KEYDOWN 129 
 int /*<<< orphan*/  IID_nsIDOMKeyEvent ; 
 int /*<<< orphan*/  NS_SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
#define  VK_F1 128 
 int /*<<< orphan*/  fire_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMEvent_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDOMKeyEvent_GetKeyCode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMKeyEvent_Release (int /*<<< orphan*/ *) ; 

HRESULT HTMLElement_handle_event(HTMLDOMNode *iface, DWORD eid, nsIDOMEvent *event, BOOL *prevent_default)
{
    HTMLElement *This = impl_from_HTMLDOMNode(iface);

    switch(eid) {
    case EVENTID_KEYDOWN: {
        nsIDOMKeyEvent *key_event;
        nsresult nsres;

        nsres = nsIDOMEvent_QueryInterface(event, &IID_nsIDOMKeyEvent, (void**)&key_event);
        if(NS_SUCCEEDED(nsres)) {
            UINT32 code = 0;

            nsIDOMKeyEvent_GetKeyCode(key_event, &code);

            switch(code) {
            case VK_F1: /* DOM_VK_F1 */
                TRACE("F1 pressed\n");
                fire_event(This->node.doc, EVENTID_HELP, TRUE, This->node.nsnode, NULL, NULL);
                *prevent_default = TRUE;
            }

            nsIDOMKeyEvent_Release(key_event);
        }
    }
    }

    return S_OK;
}