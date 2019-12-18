#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIWebBrowserSetup ;
struct TYPE_7__ {scalar_t__ scriptmode; TYPE_2__* doc_obj; } ;
struct TYPE_6__ {TYPE_1__* nscontainer; } ;
struct TYPE_5__ {int /*<<< orphan*/  webbrowser; } ;
typedef  scalar_t__ SCRIPTMODE ;
typedef  TYPE_3__ HTMLOuterWindow ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_nsIWebBrowserSetup ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ NS_SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ SCRIPTMODE_ACTIVESCRIPT ; 
 scalar_t__ SCRIPTMODE_GECKO ; 
 int /*<<< orphan*/  SETUP_ALLOW_JAVASCRIPT ; 
 int /*<<< orphan*/  SETUP_DISABLE_NOSCRIPT ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int TRUE ; 
 int /*<<< orphan*/  is_jscript_available () ; 
 int /*<<< orphan*/  nsIWebBrowserSetup_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIWebBrowserSetup_SetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nsIWebBrowser_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 

void set_script_mode(HTMLOuterWindow *window, SCRIPTMODE mode)
{
    nsIWebBrowserSetup *setup;
    nsresult nsres;

    if(mode == SCRIPTMODE_ACTIVESCRIPT && !is_jscript_available()) {
        TRACE("jscript.dll not available\n");
        window->scriptmode = SCRIPTMODE_GECKO;
        return;
    }

    window->scriptmode = mode;

    if(!window->doc_obj->nscontainer || !window->doc_obj->nscontainer->webbrowser)
        return;

    nsres = nsIWebBrowser_QueryInterface(window->doc_obj->nscontainer->webbrowser,
            &IID_nsIWebBrowserSetup, (void**)&setup);
    if(NS_SUCCEEDED(nsres)) {
        nsres = nsIWebBrowserSetup_SetProperty(setup, SETUP_ALLOW_JAVASCRIPT,
                window->scriptmode == SCRIPTMODE_GECKO);

        if(NS_SUCCEEDED(nsres))
            nsres = nsIWebBrowserSetup_SetProperty(setup, SETUP_DISABLE_NOSCRIPT, TRUE);

        nsIWebBrowserSetup_Release(setup);
    }

    if(NS_FAILED(nsres))
        ERR("JavaScript setup failed: %08x\n", nsres);
}