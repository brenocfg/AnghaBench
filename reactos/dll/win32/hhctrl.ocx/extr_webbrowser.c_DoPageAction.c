#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  web_browser; } ;
typedef  TYPE_1__ WebBrowserContainer ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  IWebBrowser2_ExecWB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWebBrowser2_GoBack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWebBrowser2_GoForward (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWebBrowser2_GoHome (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWebBrowser2_GoSearch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWebBrowser2_Refresh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWebBrowser2_Stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OLECMDEXECOPT_DONTPROMPTUSER ; 
 int /*<<< orphan*/  OLECMDID_PRINT ; 
#define  WB_GOBACK 134 
#define  WB_GOFORWARD 133 
#define  WB_GOHOME 132 
#define  WB_PRINT 131 
#define  WB_REFRESH 130 
#define  WB_SEARCH 129 
#define  WB_STOP 128 

void DoPageAction(WebBrowserContainer *container, DWORD dwAction)
{
    if (!container || !container->web_browser)
        return;

    switch (dwAction)
    {
        case WB_GOBACK:
            IWebBrowser2_GoBack(container->web_browser);
            break;
        case WB_GOFORWARD:
            IWebBrowser2_GoForward(container->web_browser);
            break;
        case WB_GOHOME:
            IWebBrowser2_GoHome(container->web_browser);
            break;
        case WB_SEARCH:
            IWebBrowser2_GoSearch(container->web_browser);
            break;
        case WB_REFRESH:
            IWebBrowser2_Refresh(container->web_browser);
            break;
        case WB_STOP:
            IWebBrowser2_Stop(container->web_browser);
            break;
        case WB_PRINT:
            IWebBrowser2_ExecWB(container->web_browser, OLECMDID_PRINT, OLECMDEXECOPT_DONTPROMPTUSER, 0, 0);
            break;
    }
}