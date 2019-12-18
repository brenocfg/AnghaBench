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
typedef  enum content { ____Placeholder_content } content ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/ * LPCOLESTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 scalar_t__ CLSIDFromProgID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CLSIDFromString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLSID_WebBrowser ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int IsEmpty ; 
 int IsGUID ; 
 int IsHTML ; 
 int IsURL ; 
 int IsUnknown ; 
 int MAX_PATH ; 
 scalar_t__ PathIsURLW (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int URL_APPLY_GUESSFILE ; 
 int URL_APPLY_GUESSSCHEME ; 
 scalar_t__ UrlApplySchemeW (int /*<<< orphan*/ *,char*,int*,int) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _wcsnicmp (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum content get_content_type(LPCOLESTR name, CLSID *control_id)
{
    static const WCHAR mshtml_prefixW[] = {'m','s','h','t','m','l',':',0};
    WCHAR new_urlW[MAX_PATH];
    DWORD size = MAX_PATH;

    if (!name || !name[0])
    {
        WARN("name %s\n", wine_dbgstr_w(name));
        return IsEmpty;
    }

    if (CLSIDFromString(name, control_id) == S_OK ||
        CLSIDFromProgID(name, control_id) == S_OK)
        return IsGUID;

    if (PathIsURLW (name) ||
        UrlApplySchemeW(name, new_urlW, &size, URL_APPLY_GUESSSCHEME|URL_APPLY_GUESSFILE) == S_OK)
    {
        *control_id = CLSID_WebBrowser;
        return IsURL;
    }

    if (!_wcsnicmp(name, mshtml_prefixW, 7))
    {
        FIXME("mshtml prefix not implemented\n");
        *control_id = CLSID_WebBrowser;
        return IsHTML;
    }

    return IsUnknown;
}