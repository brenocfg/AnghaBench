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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  OSVERSIONINFOW ;
typedef  int /*<<< orphan*/  IDxDiagContainerImpl_Container ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const**) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  add_bstr_property (int /*<<< orphan*/ *,char const*,char const*) ; 

__attribute__((used)) static HRESULT fill_os_string_information(IDxDiagContainerImpl_Container *node, OSVERSIONINFOW *info)
{
    static const WCHAR winxpW[] = {'W','i','n','d','o','w','s',' ','X','P',' ','P','r','o','f','e','s','s','i','o','n','a','l',0};
    static const WCHAR szOSLocalized[] = {'s','z','O','S','L','o','c','a','l','i','z','e','d',0};
    static const WCHAR szOSExLocalized[] = {'s','z','O','S','E','x','L','o','c','a','l','i','z','e','d',0};
    static const WCHAR szOSExLongLocalized[] = {'s','z','O','S','E','x','L','o','n','g','L','o','c','a','l','i','z','e','d',0};
    static const WCHAR szOSEnglish[] = {'s','z','O','S','E','n','g','l','i','s','h',0};
    static const WCHAR szOSExEnglish[] = {'s','z','O','S','E','x','E','n','g','l','i','s','h',0};
    static const WCHAR szOSExLongEnglish[] = {'s','z','O','S','E','x','L','o','n','g','E','n','g','l','i','s','h',0};

    static const WCHAR *prop_list[] = {szOSLocalized, szOSExLocalized, szOSExLongLocalized,
                                       szOSEnglish, szOSExEnglish, szOSExLongEnglish};

    size_t i;
    HRESULT hr;

    /* FIXME: OS detection should be performed, and localized OS strings
     * should contain translated versions of the "build" phrase. */
    for (i = 0; i < ARRAY_SIZE(prop_list); i++)
    {
        hr = add_bstr_property(node, prop_list[i], winxpW);
        if (FAILED(hr))
            return hr;
    }

    return S_OK;
}