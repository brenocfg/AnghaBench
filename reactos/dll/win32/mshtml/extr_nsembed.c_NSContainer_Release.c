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
struct TYPE_4__ {int /*<<< orphan*/  nsIWebBrowserChrome_iface; int /*<<< orphan*/ * hwnd; int /*<<< orphan*/ * content_listener; int /*<<< orphan*/ * editor; int /*<<< orphan*/ * editor_controller; int /*<<< orphan*/ * focus; int /*<<< orphan*/ * window; int /*<<< orphan*/ * navigation; int /*<<< orphan*/ * webbrowser; int /*<<< orphan*/ * doc; } ;
typedef  TYPE_1__ NSContainer ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SetParent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  nsIBaseWindow_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIBaseWindow_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIBaseWindow_SetVisibility (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIController_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIEditor_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIURIContentListener_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIWebBrowserChrome_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIWebBrowserFocus_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIWebBrowser_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIWebBrowser_SetContainerWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIWebNavigation_Release (int /*<<< orphan*/ *) ; 

void NSContainer_Release(NSContainer *This)
{
    TRACE("(%p)\n", This);

    This->doc = NULL;

    ShowWindow(This->hwnd, SW_HIDE);
    SetParent(This->hwnd, NULL);

    nsIBaseWindow_SetVisibility(This->window, FALSE);
    nsIBaseWindow_Destroy(This->window);

    nsIWebBrowser_SetContainerWindow(This->webbrowser, NULL);

    nsIWebBrowser_Release(This->webbrowser);
    This->webbrowser = NULL;

    nsIWebNavigation_Release(This->navigation);
    This->navigation = NULL;

    nsIBaseWindow_Release(This->window);
    This->window = NULL;

    nsIWebBrowserFocus_Release(This->focus);
    This->focus = NULL;

    if(This->editor_controller) {
        nsIController_Release(This->editor_controller);
        This->editor_controller = NULL;
    }

    if(This->editor) {
        nsIEditor_Release(This->editor);
        This->editor = NULL;
    }

    if(This->content_listener) {
        nsIURIContentListener_Release(This->content_listener);
        This->content_listener = NULL;
    }

    if(This->hwnd) {
        DestroyWindow(This->hwnd);
        This->hwnd = NULL;
    }

    nsIWebBrowserChrome_Release(&This->nsIWebBrowserChrome_iface);
}