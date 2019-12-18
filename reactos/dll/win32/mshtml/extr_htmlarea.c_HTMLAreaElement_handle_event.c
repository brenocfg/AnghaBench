#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMEvent ;
typedef  int /*<<< orphan*/  nsAString ;
struct TYPE_5__ {int /*<<< orphan*/  node; } ;
struct TYPE_4__ {TYPE_3__ element; int /*<<< orphan*/  nsarea; } ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;
typedef  TYPE_1__ HTMLAreaElement ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENTID_CLICK ; 
 int /*<<< orphan*/  HTMLElement_handle_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_link_click_event (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLAreaElement_GetHref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLAreaElement_GetTarget (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT HTMLAreaElement_handle_event(HTMLDOMNode *iface, DWORD eid, nsIDOMEvent *event, BOOL *prevent_default)
{
    HTMLAreaElement *This = impl_from_HTMLDOMNode(iface);
    nsAString href_str, target_str;
    nsresult nsres;

    if(eid == EVENTID_CLICK) {
        nsAString_Init(&href_str, NULL);
        nsres = nsIDOMHTMLAreaElement_GetHref(This->nsarea, &href_str);
        if (NS_FAILED(nsres)) {
            ERR("Could not get area href: %08x\n", nsres);
            goto fallback;
        }

        nsAString_Init(&target_str, NULL);
        nsres = nsIDOMHTMLAreaElement_GetTarget(This->nsarea, &target_str);
        if (NS_FAILED(nsres)) {
            ERR("Could not get area target: %08x\n", nsres);
            goto fallback;
        }

        return handle_link_click_event(&This->element, &href_str, &target_str, event, prevent_default);

fallback:
        nsAString_Finish(&href_str);
        nsAString_Finish(&target_str);
    }

    return HTMLElement_handle_event(&This->element.node, eid, event, prevent_default);
}