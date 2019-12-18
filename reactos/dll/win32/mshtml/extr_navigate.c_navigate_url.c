#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  HTMLOuterWindow ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CoInternetCombineUrlEx (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int URL_DONT_ESCAPE_EXTRA_INFO ; 
 int URL_ESCAPE_SPACES_ONLY ; 
 int /*<<< orphan*/  create_uri (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  navigate_uri (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  translate_uri (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

HRESULT navigate_url(HTMLOuterWindow *window, const WCHAR *new_url, IUri *base_uri, DWORD flags)
{
    IUri *uri, *nav_uri;
    BSTR display_uri;
    HRESULT hres;

    if(new_url && base_uri)
        hres = CoInternetCombineUrlEx(base_uri, new_url, URL_ESCAPE_SPACES_ONLY|URL_DONT_ESCAPE_EXTRA_INFO,
                &nav_uri, 0);
    else
        hres = create_uri(new_url, 0, &nav_uri);
    if(FAILED(hres))
        return hres;

    hres = translate_uri(window, nav_uri, &display_uri, &uri);
    IUri_Release(nav_uri);
    if(FAILED(hres))
        return hres;

    hres = navigate_uri(window, uri, display_uri, NULL, flags);
    IUri_Release(uri);
    SysFreeString(display_uri);
    return hres;
}