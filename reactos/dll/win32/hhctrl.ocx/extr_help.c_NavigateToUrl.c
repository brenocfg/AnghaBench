#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_10__ {int /*<<< orphan*/  chm_index; int /*<<< orphan*/  chm_file; } ;
struct TYPE_9__ {TYPE_1__* pCHMInfo; } ;
struct TYPE_8__ {int /*<<< orphan*/  szFile; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ HHInfo ;
typedef  TYPE_3__ ChmPath ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  NavigateToChm (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetChmPath (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  navigate_url (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ wcsstr (int /*<<< orphan*/ ,char const*) ; 

BOOL NavigateToUrl(HHInfo *info, LPCWSTR surl)
{
    ChmPath chm_path;
    BOOL ret;
    HRESULT hres;

    static const WCHAR url_indicator[] = {':', '/', '/', 0};

    TRACE("%s\n", debugstr_w(surl));

    if (wcsstr(surl, url_indicator)) {
        hres = navigate_url(info, surl);
        if(SUCCEEDED(hres))
            return TRUE;
    } /* look up in chm if it doesn't look like a full url */

    SetChmPath(&chm_path, info->pCHMInfo->szFile, surl);
    ret = NavigateToChm(info, chm_path.chm_file, chm_path.chm_index);

    heap_free(chm_path.chm_file);
    heap_free(chm_path.chm_index);

    return ret;
}