#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* doc_obj; } ;
struct TYPE_4__ {scalar_t__ hostui; } ;
typedef  int /*<<< orphan*/  OLECHAR ;
typedef  int /*<<< orphan*/  IUri ;
typedef  TYPE_2__ HTMLOuterWindow ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDocHostUIHandler_TranslateUrl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IUri_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUri_GetDisplayUri (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_uri (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT translate_uri(HTMLOuterWindow *window, IUri *orig_uri, BSTR *ret_display_uri, IUri **ret_uri)
{
    IUri *uri = NULL;
    BSTR display_uri;
    HRESULT hres;

    hres = IUri_GetDisplayUri(orig_uri, &display_uri);
    if(FAILED(hres))
        return hres;

    if(window->doc_obj && window->doc_obj->hostui) {
        OLECHAR *translated_url = NULL;

        hres = IDocHostUIHandler_TranslateUrl(window->doc_obj->hostui, 0, display_uri,
                &translated_url);
        if(hres == S_OK && translated_url) {
            TRACE("%08x %s -> %s\n", hres, debugstr_w(display_uri), debugstr_w(translated_url));
            SysFreeString(display_uri);
            hres = create_uri(translated_url, 0, &uri);
            CoTaskMemFree(translated_url);
            if(FAILED(hres))
                return hres;

            hres = IUri_GetDisplayUri(uri, &display_uri);
            if(FAILED(hres)) {
                IUri_Release(uri);
                return hres;
            }
        }
    }

    if(!uri) {
        IUri_AddRef(orig_uri);
        uri = orig_uri;
    }

    *ret_display_uri = display_uri;
    *ret_uri = uri;
    return S_OK;
}