#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsAString ;
struct TYPE_14__ {TYPE_3__* doc; } ;
struct TYPE_16__ {TYPE_4__ node; } ;
struct TYPE_11__ {int /*<<< orphan*/  IHTMLWindow2_iface; } ;
struct TYPE_15__ {TYPE_1__ base; int /*<<< orphan*/  uri_nofrag; } ;
struct TYPE_12__ {int /*<<< orphan*/  window; } ;
struct TYPE_13__ {TYPE_2__ basedoc; } ;
typedef  scalar_t__ PRUnichar ;
typedef  TYPE_5__ HTMLOuterWindow ;
typedef  TYPE_6__ HTMLElement ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BINDING_NAVIGATED ; 
 int /*<<< orphan*/  IHTMLWindow2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 TYPE_5__* get_target_window (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  navigate_href_new_window (TYPE_6__*,int /*<<< orphan*/ *,scalar_t__ const*) ; 
 int /*<<< orphan*/  navigate_url (TYPE_5__*,scalar_t__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,scalar_t__ const**) ; 

__attribute__((used)) static HRESULT navigate_href(HTMLElement *element, nsAString *href_str, nsAString *target_str)
{
    HTMLOuterWindow *window;
    BOOL use_new_window;
    const PRUnichar *href;
    HRESULT hres;

    window = get_target_window(element->node.doc->basedoc.window, target_str, &use_new_window);
    if(!window) {
        if(use_new_window) {
            const PRUnichar *target;
            nsAString_GetData(target_str, &target);
            return navigate_href_new_window(element, href_str, target);
        }else {
            return S_OK;
        }
    }

    nsAString_GetData(href_str, &href);
    if(*href) {
        hres = navigate_url(window, href, window->uri_nofrag, BINDING_NAVIGATED);
    }else {
        TRACE("empty href\n");
        hres = S_OK;
    }
    IHTMLWindow2_Release(&window->base.IHTMLWindow2_iface);
    return hres;
}