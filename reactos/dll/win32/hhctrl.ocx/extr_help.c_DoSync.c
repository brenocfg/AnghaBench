#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  pszFile; } ;
struct TYPE_9__ {int /*<<< orphan*/  content; TYPE_2__* tabs; TYPE_1__ WinType; TYPE_3__* web_browser; } ;
struct TYPE_8__ {int /*<<< orphan*/  web_browser; } ;
struct TYPE_7__ {int /*<<< orphan*/  hwnd; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_4__ HHInfo ;
typedef  char* BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ActivateContentTopic (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AppendFullPathURL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int INTERNET_MAX_URL_LENGTH ; 
 int /*<<< orphan*/  IWebBrowser2_get_LocationURL (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  SysFreeString (char*) ; 
 size_t TAB_CONTENTS ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ lstrcmpiW (char*,char*) ; 
 scalar_t__ lstrlenW (char*) ; 
 char* wcsstr (char*,char const*) ; 

__attribute__((used)) static void DoSync(HHInfo *info)
{
    WCHAR buf[INTERNET_MAX_URL_LENGTH];
    HRESULT hres;
    BSTR url;

    hres = IWebBrowser2_get_LocationURL(info->web_browser->web_browser, &url);

    if (FAILED(hres))
    {
        WARN("get_LocationURL failed: %08x\n", hres);
        return;
    }

    /* If we're not currently viewing a page in the active .chm file, abort */
    if ((!AppendFullPathURL(info->WinType.pszFile, buf, NULL)) || (lstrlenW(buf) > lstrlenW(url)))
    {
        SysFreeString(url);
        return;
    }

    if (lstrcmpiW(buf, url) > 0)
    {
        static const WCHAR delimW[] = {':',':','/',0};
        const WCHAR *index;

        index = wcsstr(url, delimW);

        if (index)
            ActivateContentTopic(info->tabs[TAB_CONTENTS].hwnd, index + 3, info->content); /* skip over ::/ */
    }

    SysFreeString(url);
}